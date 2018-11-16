from maxdb import *

db = DB('db.json', storage=JSONStorage)

"""Creating tables and adding rows."""
# users = db.table(
#     'Users',
#     columns={
#         'fname': 'str',
#         'sname': 'str'
#     },
#     cache_size=20
# )
# books = db.table(
#     'Books',
#     columns={
#         'author': 'fk',
#         'pages': 'int'
#     },
#     cache_size=20
# )
# print('Tables:', db.tables())

"""Iterate through table items"""
# for item in users:
#     print(item)

"""Adding data: insert"""
# users_inst = [
#     {
#         "fname": ("aname", "str"),
#         "sname": ("asurame", "str")
#     },
#     {
#         "fname": ("cname", "str"),
#         "sname": ("csurname", "str")
#     }
# ]
# books_inst = [
#     {
#         "author": ({'table': 'Users', 'fkid': 1}, "fk"),
#         "pages": ('123', 'int')
#     },
#     {
#         "author": ({'table': 'Users', 'fkid': 2}, 'fk'),
#         "pages": ('234', 'int')
#     }
# ]
# for user in users_inst:
#     db.insert(users.name, user)
# for book in books_inst:
#     db.insert(books.name, book)

"""Reading data: get"""
# print(users.get(1))
# print(users.get(cond=lambda i: i.value == 'aname'))
# print(users.get(cond=lambda i: i.type == 'str'))
# print(users.get(cond=lambda i: i.type == 'str_'))

"""Removing data: delete"""
# deleted_row = users.delete(row_ids=[1])  # item in books table will have value={}
# print(users._all())
# print(books._all())

"""Updating data: update"""
# fields_to_update = {
#     "pages": 999,
# }
# print('Before:', books._all())
# books.update(fields_to_update, [1])
# print('After:', books._all())

"""Searching for data"""
# query = lambda i: i.values().value == "999"
# search_query = lambda item: item['pages'].value == "999"
# print(books.search(search_query))  # query result is saved in query_LRU_cache

"""Advanced queries"""
# query = Query().pages.value == "999"
# print(books.search(query))
# print(books.search(where('pages').value == "999"))  # beauty of the quering.

db.close()
