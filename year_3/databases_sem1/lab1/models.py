class Product(object):
    def __init__(self, name, price):
        self.name = name
        self.price = price


class Order(object):
    def __init__(self, product_id, client, destination):
        self.product_id = product_id
        self.client = client
        self.destination = destination
