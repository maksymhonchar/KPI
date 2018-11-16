"""
Implementing queries for DB.


class QueryTest(object):
    A certain query test implementation.
    Wraps a test function which is run when the query is evaluated by calling the object.
    
    Hashval format: 
        val_to_be_hashed
        ('query_operation_str', [hashval1, hashval2, ...]])
    Parameter hash_val can be 
    1) self.hashval for one element to process 
    2) frozenset of hashvals of several elements to process severla elements.
    
    Queries can be combined with logical and/or and modified with logical not.

    where(...) function simplifies usage of Query class.


 class Query(object):
    A DB query implementation.
    Returns True or False if query is valid or not.

    ! Freeze commutative queries: and, or, equals.

    Usage:
    1) ORM-like usage:
    Elem = Query()
    db.search(Elem.attr = 'attr_value')  # compare as a string
    db.search(Elem['attr'] = attr_value)  # saving types
    2) SQL-like request:
    db.search(where('value') == attr_value)  # saving type
    db.search(Query('value') == attr_value)

    QueryTest implementation allows to combine queries:
    db.search(where('attr').exists() & where('attr') == attr_value)
    db.search(where('attr').exists() | where('attr') == attr_value)
"""


import re

from .utils import freeze


class QueryTest(object):
    def __init__(self, test, hashval):
        self.test = test
        self.hashval = hashval

    def __call__(self, value):
        return self.test(value)

    def __hash__(self):
        return hash(self.hashval)

    def __repr__(self):
        return 'QueryTest {0}'.format(self.hashval)

    def __eq__(self, other):
        return self.hashval == other.hashval

    def __and__(self, other):
        return QueryTest(
                test=lambda value: self(value) and other(value),
                hashval=('and', frozenset([self.hashval, other.hashval]))
                )
    
    def __or__(self, other):
        return QueryTest(
                test=lambda value: self(value) or other(value),
                hashval=('or', frozenset([self.hashval, other.hashval]))
                )
    
    def __invert__(self):
        return QueryTest(
                test=lambda value: not self(value),
                hashval=('not', self.hashval)
                )


def where(key):
    """
    Workaround for user-friendly SQL-like queries.
    """
    return Query()[key]


class Query(object):
    def __init__(self):
        self._path = []

    def __getattr__(self, item):
        query = Query()
        query._path = self._path + [item]
        return query

    __getitem__ = __getattr__

    def _generate_test(self, test, hashval):
        """
        Generate a query based on test callback function.

        param test: a code the query executes.
        returns: a QueryTest object.
        """
        if not self._path:
            raise ValueError('Cannot execute an empty Query')
        
        def impl(value):
            try:
                for part in self._path:  # get to the item to make test() with
                    # print('going to path, current value: ', value)
                    value = value[part]  # note, that __getitem__ is used, not a __getattr__
            except (KeyError, TypeError):
                return False
            else:
                # print('test with value:', value)
                return test(value)

        return QueryTest(impl, hashval)

    def action(self, func, *args):
        """
        A custom action for query.

        def my_test(value):
            return isinstance(value, str)
        Query().item.test(my_test)
        """
        return self._generate_test(
                    test=lambda value: func(value, *args),
                    hashval=('action', tuple(self._path), func, args)
                    )

    def __eq__(self, tocmp):
        """
        Query().item == item_value
        """
        return self._generate_test(
                    test=lambda value: value == tocmp,
                    hashval=('==', tuple(self._path), freeze(tocmp))
                    )
    
    def __ne__(self, tocmp):
        """
        Query().item != item_value
        """
        return self._generate_test(
                    test=lambda value: value != tocmp,
                    hashval=('!=', tuple(self._path), freeze(tocmp))
                    )

    def __lt__(self, tocmp):
        """
        Query().item < item_value
        """
        return self._generate_test(
                    test=lambda value: value < tocmp,
                    hashval=('<', tuple(self._path), tocmp)
                    )

    def __le__(self, tocmp):
        """
        Query().item <= item_value
        """
        return self._generate_test(
                    test=lambda value: value <= tocmp,
                    hashval=('<=', tuple(self._path), tocmp)
                    )

    def __gt__(self, tocmp):
        """
        Query().item > item_value
        """
        return self._generate_test(
                    test=lambda value: value > tocmp,
                    hashval=('>', tuple(self._path), tocmp)
                    )

    def __ge__(self, tocmp):
        """
        Query().item >= item_value
        """
        return self._generate_test(
                    test=lambda value: value >= tocmp,
                    hashval=('>=', tuple(self._path), tocmp)
                    )

    def exists(self):
        """
        Query().item.exists()
        """
        return self._generate_test(
                    test=lambda _: True,
                    hashval=('exists', tuple(self._path))
                    )

    def matches(self, regex):
        """
        Query().item.matches(r'^\w+$')
        """
        return self._generate_test(
                    test=lambda value: re.match(regex, value),
                    hashval=('matches', tuple(self._path), regex)
                    )
    
    def search(self, regex):
        """
        Query().item.search(r'^re_gex$')
        """
        return self._generate_test(
                    test=lambda value: re.search(regex, value),
                    hashval=('search', tuple(self._path), regex)
                    )
    
    def any(self, cond):
        """
        note: condition can be a list.
        returns: dict

        Query().item.any(Query().item2 == item_value)
        Query().item.any([True, False])
        """
        if callable(cond):
            def _cmp(value):
                return hasattr(value, '__iter__') and any(cond(e) for e in value)
        else:
            def _cmp(value):
                return hasattr(value, '__iter__') and any(e in cond for e in value)

        return self._generate_test(
                    test=lambda value: _cmp(value),
                    hashval=('any', tuple(self._path), freeze(cond))
                    )

    def all(self, cond):
        """
        note: condition can be a list.
        returns: dict

        Query().item._all(Query().item2 == item_value)
        Query().item._all([True, False])
        """
        if callable(cond):
            def _cmp(value):
                return hasattr(value, '__iter__') and all(cond(e) for e in value)

        else:
            def _cmp(value):
                return hasattr(value, '__iter__') and all(e in value for e in cond)
        
        return self._generate_test(
                    test=lambda value: _cmp(value),
                    hashval=('_all', tuple(self._path), freeze(cond))
                    )
