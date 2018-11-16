# coding=utf-8
import os
import random
import time

import numpy
import numpy as np
import psycopg2


class DbManager(object):
    def __init__(self):
        self.master_db_conn = None
        self.replica_db_conn = None
        self.master_cur = None
        self.replica_cur = None

    def open_db(self):
        self.master_db_conn = psycopg2.connect(
            'dbname=goodstrackdb user=goodstrackdb host=localhost password=pass'
        )
        self.master_cur = self.master_db_conn.cursor()
        self.replica_db_conn = psycopg2.connect(
            'dbname=goodstrackdbreplica user=goodstrackdb host=localhost password=pass'
        )
        self.replica_cur = self.replica_db_conn.cursor()

    def close_db(self):
        self.replica_cur.close()
        self.replica_db_conn.close()
        self.master_db_conn.close()
        self.master_cur.close()

    def make_backup(self):
        tables = ('1_markets', '2_cashiers', '3_receipts', '4_products', '5_productholders')
        db_cur = self.get_read_candidate()
        print 'Backup: saving INSERT .sql queries.'
        for table_name in tables:
            db_cur.execute('SELECT * FROM {0};'.format(table_name[2:]))
            datetime_now = time.strftime("%Y_%m_%d_%H_h_%M_m_%S_s")
            with open('backup/{0}_bckup_{1}.sql'.format(table_name, datetime_now), 'w') as f:
                for row in db_cur:
                    insert_data = list()
                    if table_name == '1_markets':
                        insert_data.append('(name)')
                        insert_data.append('(\'{0}\')'.format(row[1]))
                    if table_name == '2_cashiers':
                        insert_data.append('(market_id, name, experience, totalclients, totalservicesec)')
                        insert_data.append('({0}, \'{1}\', {2}, {3}, {4})'.format(row[1], row[2], row[3], row[4],
                                                                                  row[5]))
                    if table_name == '3_receipts':
                        time_sql_format = row[3].strftime("%H:%M:%S")
                        insert_data.append('(cashier_id, servicesec, timing)')
                        insert_data.append('({0}, {1}, \'{2}\')'.format(row[1], row[2], time_sql_format))
                    if table_name == '4_products':
                        insert_data.append('(category, name, price)')
                        insert_data.append('(\'{0}\', \'{1}\', {2})'.format(row[1], row[2], row[3]))
                    if table_name == '5_productholders':
                        insert_data.append('(receipt_id, product_id, weight)')
                        insert_data.append('({0}, {1}, {2})'.format(row[1], row[2], row[3]))
                    f.write('INSERT INTO {0} {1} VALUES {2};\n'.format(table_name[2:], insert_data[0], insert_data[1]))
            print '{0} backed up.'.format(table_name[2:])

    def recover_from_backup(self):
        self.create_tables()
        print 'Recovery: created old schema'
        for backup_file in sorted(os.listdir('backup/')):
            with open('backup/{0}'.format(backup_file)) as f:
                for sql_cmd in f:
                    self.master_cur.execute(sql_cmd)
                    self.master_db_conn.commit()
                    self.replica_cur.execute(sql_cmd)
                    self.replica_db_conn.commit()
            print 'Recovered from {0}'.format(backup_file)

    def create_tables(self):
        commands = (
            """
            CREATE TABLE markets (
                id SERIAL PRIMARY KEY,
                name VARCHAR(255) NOT NULL
            );
            """,
            """
            CREATE TABLE cashiers (
                id SERIAL PRIMARY KEY,
                market_id INTEGER NOT NULL,
                name VARCHAR(255) NOT NULL,
                experience REAL NOT NULL DEFAULT 1.0,
                totalclients INTEGER NOT NULL DEFAULT 0,
                totalservicesec INTEGER NOT NULL DEFAULT 0,

                FOREIGN KEY (market_id)
                    REFERENCES markets (id)
                    ON UPDATE CASCADE ON DELETE CASCADE
            );
            """,
            """
            CREATE TABLE receipts (
                id SERIAL PRIMARY KEY,
                cashier_id INTEGER NOT NULL,
                servicesec INTEGER NOT NULL DEFAULT 0,
                timing TIME NOT NULL,
            
                FOREIGN KEY (cashier_id)
                    REFERENCES cashiers (id)
                    ON UPDATE CASCADE ON DELETE CASCADE
            );
            """,
            """
            CREATE TABLE products (
                id SERIAL PRIMARY KEY,
                category VARCHAR(255) NOT NULL,
                name VARCHAR(255) NOT NULL,
                price REAL DEFAULT 0.0
            );
            """,
            """
            CREATE TABLE productholders (
                id SERIAL PRIMARY KEY,
                receipt_id INTEGER NOT NULL,
                product_id INTEGER NOT NULL,
                weight REAL NOT NULL DEFAULT 0.0,
            
                FOREIGN KEY (receipt_id)
                    REFERENCES receipts (id)
                    ON UPDATE CASCADE ON DELETE CASCADE,
                FOREIGN KEY (product_id)
                    REFERENCES products (id)
                    ON UPDATE CASCADE ON DELETE CASCADE
            );
            """
        )
        for command in commands:
            self.master_cur.execute(command)
            self.replica_cur.execute(command)
        self.master_db_conn.commit()
        self.replica_db_conn.commit()

    def fillup_db(self):
        self.create_tables()
        # Create default markets. Total: 3 rows.
        self.create_market('auchan')
        self.create_market('fora')
        self.create_market('silpo')
        # Create default cashiers. Total: 200 rows.
        names = ('vova', 'maksym', 'vanya', 'petya', 'masha', 'nadya', 'alla', 'kira')
        for name in names:
            for i in range(25):
                self.create_cashier(random.randint(1, 3), name, random.randint(10, 100) / 10)
        # Create default set of products. Total: 26 rows.
        products = {
            'vegetables': ('apple', 'pineapple', 'avocado', 'mango', 'cherry', 'feijoa', 'lemon', 'lime', 'peach'),
            'fruits': ('cabbage', 'carrot', 'potato', 'celery', 'pumpkin', 'kale', 'lettuce', 'artichoke', 'broccoli'),
            'condiments': ('mustard', 'ketchup', 'salt', 'sugar', 'chili', 'cream cheese', 'barbecue sauce',
                           'garlic sauce'),
        }
        for cat in products.keys():
            for prod_name in products.get(cat):
                self.create_product(cat, prod_name, random.randint(100, 1000) / 10.0)

    def get_read_candidate(self):
        is_slave = random.randint(0, 3)  # 0 for master; 1,2,3 for slave
        if is_slave:
            # print 'Read from slave - replica.'
            return self.replica_cur
        else:
            # print 'Read from master.'
            return self.master_cur

    def create_market(self, m_name):
        insert_sql = """INSERT INTO markets (name)
                        VALUES(%s);"""
        self.master_cur.execute(insert_sql, (m_name,))
        self.master_db_conn.commit()
        self.replica_cur.execute(insert_sql, (m_name,))
        self.replica_db_conn.commit()

    def create_cashier(self, c_market_id, c_name, c_experience):
        insert_sql = """INSERT INTO cashiers (market_id, name, experience)
                        VALUES(%s, %s, %s);"""
        self.master_cur.execute(insert_sql, (c_market_id, c_name, c_experience))
        self.master_db_conn.commit()
        self.replica_cur.execute(insert_sql, (c_market_id, c_name, c_experience))
        self.replica_db_conn.commit()

    def create_receipt(self, r_cashier_id, r_service_sec, r_timing):
        insert_sql = """INSERT INTO receipts (cashier_id, servicesec, timing)
                        VALUES(%s, %s, %s) RETURNING id;"""
        # Create new receipt.
        self.master_cur.execute(insert_sql, (r_cashier_id, r_service_sec, r_timing))
        inserted_id = self.master_cur.fetchone()[0]
        self.master_db_conn.commit()
        self.replica_cur.execute(insert_sql, (r_cashier_id, r_service_sec, r_timing))
        self.replica_db_conn.commit()
        # Update existing cashier.
        update_totalclients_sql = """UPDATE cashiers SET totalclients=totalclients+1 WHERE id=(%s);"""
        update_servicetime_sql = """UPDATE cashiers SET totalservicesec=totalservicesec+(%s) WHERE id=(%s);"""
        self.master_cur.execute(update_totalclients_sql, (r_cashier_id,))
        self.master_cur.execute(update_servicetime_sql, (r_service_sec, r_cashier_id))
        self.master_db_conn.commit()
        self.replica_cur.execute(update_totalclients_sql, (r_cashier_id,))
        self.replica_cur.execute(update_servicetime_sql, (r_service_sec, r_cashier_id))
        self.replica_db_conn.commit()
        return inserted_id

    def create_productholder(self, ph_receipt_id, ph_product_id, ph_weight):
        insert_sql = """INSERT INTO productholders (receipt_id, product_id, weight)
                        VALUES(%s, %s, %s);"""
        self.master_cur.execute(insert_sql, (ph_receipt_id, ph_product_id, ph_weight))
        self.master_db_conn.commit()
        self.replica_cur.execute(insert_sql, (ph_receipt_id, ph_product_id, ph_weight))
        self.replica_db_conn.commit()

    def create_product(self, p_category, p_name, p_price):
        insert_sql = """INSERT INTO products (category, name, price)
                        VALUES(%s, %s, %s);"""
        self.master_cur.execute(insert_sql, (p_category, p_name, p_price))
        self.master_db_conn.commit()
        self.replica_cur.execute(insert_sql, (p_category, p_name, p_price))
        self.replica_db_conn.commit()

    def get_markets_ids(self):
        get_markets_sql = """SELECT id FROM markets;"""
        db_cur = self.get_read_candidate()
        db_cur.execute(get_markets_sql)
        return db_cur.fetchall()

    def get_cashiers_ids_by_market(self, market_id):
        get_cashiers_by_market_sql = """SELECT id FROM cashiers WHERE market_id=(%s);"""
        db_cur = self.get_read_candidate()
        db_cur.execute(get_cashiers_by_market_sql, (market_id,))
        return db_cur.fetchall()

    def get_cashier_by_id(self, cashier_id):
        get_sql = """SELECT * FROM cashiers WHERE id=(%s);"""
        db_cur = self.get_read_candidate()
        db_cur.execute(get_sql, (cashier_id,))
        return db_cur.fetchone()

    def get_product_ids(self):
        get_sql = """SELECT id FROM products;"""
        db_cur = self.get_read_candidate()
        db_cur.execute(get_sql)
        return db_cur.fetchall()

    def get_product_cats(self):
        get_sql = """SELECT category FROM products;"""
        db_cur = self.get_read_candidate()
        db_cur.execute(get_sql)
        all_cats_duplicated = db_cur.fetchall()
        np_all_cats_duplicated = np.array([cat[0] for cat in all_cats_duplicated])
        unique, counts = numpy.unique(np_all_cats_duplicated, return_counts=True)
        return unique

    def get_product_name_category(self, prod_id):
        get_sql = """SELECT name, category FROM products WHERE id=(%s);"""
        db_cur = self.get_read_candidate()
        db_cur.execute(get_sql, (prod_id,))
        return db_cur.fetchone()

    def get_receipt_price(self, receipt_id):
        get_purchases_sql = """SELECT product_id, weight FROM productholders WHERE receipt_id=(%s);"""
        get_products_sql = """SELECT * from products;"""
        db_cur = self.get_read_candidate()

        # Get purchases.
        db_cur.execute(get_purchases_sql, (receipt_id,))
        all_raw_purchases = db_cur.fetchall()
        # Get all products.
        db_cur.execute(get_products_sql)
        all_raw_products = db_cur.fetchall()
        # Transform all raw purchases and all raw products to numpy array.
        purchases = [list(row) for row in all_raw_purchases]
        products = [list(row) for row in all_raw_products]
        # Get sum of all products in single receipt.
        receipt_sum = 0.0
        for (prod_id, weight) in purchases:
            product = products[int(prod_id) - 1]
            product_price = float(product[3]) * weight
            receipt_sum += product_price
        # Return receipt price.
        return receipt_sum

    def get_receipt_average_price_by_market(self, market_id):
        get_cashiers_sql = """SELECT * FROM cashiers WHERE market_id=(%s);"""
        get_receipts_sql = """SELECT * from receipts WHERE cashier_id=(%s);"""
        db_cur = self.get_read_candidate()

        # Get market cashiers from certain market.
        db_cur.execute(get_cashiers_sql, (market_id,))
        all_raw_cashiers = db_cur.fetchall()
        # Get all receipts from certain market.
        all_raw_receipts = list()
        for raw_cashier in all_raw_cashiers:
            db_cur.execute(get_receipts_sql, (raw_cashier[0],))
            cashier_receipts = db_cur.fetchall()
            all_raw_receipts.extend(cashier_receipts)
        # Get price for each receipt.
        receipts_ids = [receipt[0] for receipt in all_raw_receipts]
        receipt_prices = [self.get_receipt_price(rec_id) for rec_id in receipts_ids]
        # Create NP array object.
        np_prices = np.array(receipt_prices)
        average_price = np.mean(np_prices)
        median_price = np.median(np_prices)
        return average_price, median_price

    def get_product_popularity(self, product_id):
        get_all_purchases_sql = """SELECT product_id FROM productholders;"""
        db_cur = self.get_read_candidate()

        # Get list of all purchases.
        db_cur.execute(get_all_purchases_sql)
        all_raw_purchases = db_cur.fetchall()
        total_amount_of_purchases = float(len(all_raw_purchases))

        # Create numpy array out of all purchases ids.
        np_all_purchases_ids = np.array([purchase[0] for purchase in all_raw_purchases])
        unique_id, counts = numpy.unique(np_all_purchases_ids, return_counts=True)
        products_popularity = dict(zip(unique_id, counts))

        # Amount of purchases of a needed product from func args.
        needed_product_count = products_popularity.get(product_id[0])

        # Get and return popularity of single product.
        products_popularity = needed_product_count / total_amount_of_purchases
        return products_popularity

    def get_product_category_popularity(self, product_cat):
        get_all_purchases_sql = """SELECT product_id FROM productholders;"""
        db_cur = self.get_read_candidate()

        # Get list of all purchases.
        db_cur.execute(get_all_purchases_sql)
        all_raw_purchases = db_cur.fetchall()

        # Get list of all products bought.
        categories_bought = list()
        for prod_id in all_raw_purchases:
            _, prod_cat = self.get_product_name_category(prod_id)
            categories_bought.append(prod_cat)

        # Create numpy array out of all categories names.
        np_all_categories = np.array(categories_bought)
        unique, counts = numpy.unique(np_all_categories, return_counts=True)
        cats_dict = dict(zip(unique, counts))

        # Get popularity of certain product category.
        sum_counts = float(sum(cats_dict.values()))
        popularity = cats_dict.get(product_cat) / sum_counts

        return popularity

    def get_products_price_range_popularity(self, min_range, max_range):
        get_products_prices_sql = """SELECT id, name, price FROM products;"""
        db_cur = self.get_read_candidate()

        # Get list of all products.
        db_cur.execute(get_products_prices_sql)
        all_products = db_cur.fetchall()

        # Get products in range:
        products_in_range = dict()
        for prod_id, product_name, price in all_products:
            if min_range <= price < max_range:
                products_in_range[prod_id] = product_name

        # Get sum popularity for the range:
        sum_popularity = 0.0
        for prod_id in products_in_range.keys():
            prod_popularity = self.get_product_popularity((prod_id,))
            sum_popularity += prod_popularity

        # Return collected summary popularity.
        return sum_popularity
