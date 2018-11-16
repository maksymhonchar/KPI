# coding=utf-8
import random
import time
from dbwrapper import DbManager


def get_new_hour(cur_hour):
    if cur_hour == 24:
        return 1
    return cur_hour + 1


def mainloop(db_manager):
    while True:
        # Writes. 1 hour = 20 writes.
        # write_start_time = time.time()
        # for i in range(20):
        #     market_id = random.choice(db_manager.get_markets_ids())
        #     cashier_id = random.choice(db_manager.get_cashiers_ids_by_market(market_id))
        #     cashier = db_manager.get_cashier_by_id(cashier_id)
        #     receipt_id = db_manager.create_receipt(
        #         cashier_id[0], random.randint(1, 100) / cashier[3], time.strftime("%H:%M:%S")
        #     )
        #     purch_products_ids = random.sample(range(1, 26+1), random.randint(1, 26))
        #     for prod_id in purch_products_ids:
        #         random_weight = random.randint(1, 10) / 10.0
        #         db_manager.create_productholder(
        #             receipt_id, prod_id, random_weight
        #         )
        # write_end_time = time.time()
        # print 'Writing 20 receipts took [{0}] seconds.'.format(write_end_time - write_start_time)

        # Reads.
        read_start_time = time.time()
        # Average receipt price, median receipt price.
        average_receipt_price_by_market_1 = db_manager.get_receipt_average_price_by_market(1)
        average_receipt_price_by_market_2 = db_manager.get_receipt_average_price_by_market(2)
        average_receipt_price_by_market_3 = db_manager.get_receipt_average_price_by_market(3)
        print '\n---\n\nСЕРЕДНІЙ ЧЕК. МЕДІАНА СЕРЕДНЬОГО ЧЕКУ.'
        print 'Auchan: Середній чек: {0}. Медіана середнього чеку: {1}.'.format(*average_receipt_price_by_market_1)
        print 'Fora: Середній чек: {0}. Медіана середнього чеку: {1}.'.format(*average_receipt_price_by_market_2)
        print 'Silpo: Середній чек: {0}. Медіана середнього чеку: {1}.'.format(*average_receipt_price_by_market_3)
        # Popularity of certain product.
        print '\n---\n\nПОПУЛЯРНІСТЬ ТОВАРІВ ПО МЕРЕЖІ ТРЬОХ МАРКЕТІВ.'
        for product_id in db_manager.get_product_ids():
            prod_name, _ = db_manager.get_product_name_category(product_id)
            prod_popularity = db_manager.get_product_popularity(product_id)
            print 'Популярність продукту {0} - [{1}]'.format(prod_name, prod_popularity)
        # Popularity of certain category.
        print '\n---\n\nПОПУЛЯРНІСТЬ КАТЕГОРІЇ ТОВАРІВ ПО МЕРЕЖІ ТРЬОХ МАРКЕТІВ.'
        for product_cat in db_manager.get_product_cats():
            product_cat_popularity = db_manager.get_product_category_popularity(product_cat)
            print 'Популярність категорії {0} - [{1}]'.format(product_cat, product_cat_popularity)
        # Price in ranges: [0;30], [30;60], [60;100].
        print '\n---\n\nПОПУЛЯРНІСТЬ ТОВАРІВ ЗА ЦІНОВИМИ ПРОМІЖКАМИ.'
        pop_products_0_30 = db_manager.get_products_price_range_popularity(0, 30)
        pop_products_30_60 = db_manager.get_products_price_range_popularity(30, 60)
        pop_products_60_100 = db_manager.get_products_price_range_popularity(60, 100)
        print 'Продукти у межах 0-30 грн: [{0}]'.format(pop_products_0_30)
        print 'Продукти у межах 30-60 грн: [{0}]'.format(pop_products_30_60)
        print 'Продукти у межах 60-100 грн: [{0}]'.format(pop_products_60_100)

        read_end_time = time.time()
        print '\nGetting special data (reads) took [{0}] seconds'.format(read_end_time - read_start_time)

        # Print reads.

        break

        # todo: reads + reads_time
        # todo: print reads
        # todo: print (writes_time, reads_time)

        # todo: wait for [enter] input == next day.


if __name__ == '__main__':
    dbm = DbManager()
    dbm.open_db()

    mainloop(dbm)

    # try:
    #     mainloop(dbm)
    # except Exception as e:
    #     print('Exception caught in mainloop: {0}'.format(e))
    #     dbm.close_db()

    # Fillup with dummy data (no purchases):
    # dbm.fillup_db()

    # Backup-Recovery:
    # dbm.make_backup()
    # dbm.recover_from_backup()

    dbm.close_db()
