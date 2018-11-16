class Market(object):
    def __init__(self, market_id,
                 market_name):
        self.id = market_id
        self.name = market_name


class Cashier(object):
    def __init__(self, cashier_id, cashier_market_id,
                 cashier_name, cashier_experience, cashier_totalclients, cashier_totalservicesec):
        self.id = cashier_id
        self.market = cashier_market_id
        self.name = cashier_name
        self.experience = cashier_experience
        self.total_clients = cashier_totalclients
        self.total_service_sec = cashier_totalservicesec


class Receipt(object):
    def __init__(self, receipt_id, receipt_cashier_id, receipt_productholder_id,
                 receipt_service_sec, receipt_timestamp):
        self.id = receipt_id
        self.cashier = receipt_cashier_id
        self.productholder = receipt_productholder_id
        self.service_sec = receipt_service_sec
        self.timestamp = receipt_timestamp


class ProductHolder(object):
    def __init__(self, pholder_receipt_id, pholder_product_id,
                 pholder_weight):
        self.receipt = pholder_receipt_id
        self.product = pholder_product_id
        self.weight = pholder_weight


class Product(object):
    def __init__(self, product_id,
                 product_category, product_name, product_price):
        self.id = product_id
        self.category = product_category
        self.name = product_name
        self.price = product_price
