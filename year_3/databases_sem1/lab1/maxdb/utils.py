"""
Utilities for maxdb classes.
"""

import os


class LRUCache(dict):
    """
    LRU: least recently used cache - default storage for queries.

    Available functionality:
        get item: .get or __getitem__
        put item: __setitem__
        del item: .clear or __delitem__

    """

    def __init__(self, *args, **kw):
        self.capacity = kw.pop('capacity', None) or float('nan')
        self.lru = []
        super(LRUCache, self).__init__(*args, **kw)

    def _refresh(self, key):
        if key in self.lru:
            self.lru.remove(key)
        self.lru.append(key)

    def get(self, key, default=None):
        item = super(LRUCache, self).get(key, default)
        self._refresh(key)
        return item

    def clear(self):
        super(LRUCache, self).clear()
        del self.lru[:]

    def __getitem__(self, key):
        item = super(LRUCache, self).__getitem__(key)
        self._refresh(key)
        return item

    def __setitem__(self, key, value):
        super(LRUCache, self).__setitem__(key, value)
        self._refresh(key)
        if len(self) >= self.capacity:
            self.pop(self.lru.pop(0))
    
    def __delitem__(self, key):
        super(LRUCache, self).__delitem__(key)
        self.lru.remove(key)


class FrozenDict(dict):
    """
    An immutable dict to save into db.
    Usage in maxdb: through 'freeze' method.
    """

    def __hash__(self):
        return hash(tuple(sorted(self.items())))

    def _immutable(self, *args, **kw):
        raise TypeError('FrozenDict is immutable')

    __setitem__ = _immutable
    __delitem__ = _immutable
    clear = _immutable
    update = _immutable
    setdefault = _immutable
    pop = _immutable
    popitem = _immutable


def freeze(obj):
    """
    Make an object immutable to store it as an element in DB.
    
    The whole idea of freezing elements:
    1) sort of encapsulation
    2) queries are commutative:
        (a|b == b|a) or (a&b == b&a)
    """
    if isinstance(obj, dict):
        return FrozenDict((k, freeze(v)) for k, v in obj.items())
    elif isinstance(obj, list):
        return tuple(freeze(el) for el in obj)
    elif isinstance(obj, set):
        return frozenset(obj)
    else:
        return obj


def touch(fname, create_dirs):
    if create_dirs:
        base_dir = os.path.dirname(fname)
        if not os.path.exists(base_dir):
            os.makedirs(base_dir)
    with open(fname, 'a'):
        os.utime(fname, None)
