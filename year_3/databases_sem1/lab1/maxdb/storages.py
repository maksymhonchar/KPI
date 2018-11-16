from abc import ABCMeta, abstractmethod
from .dbelement import DBElement, DBFKElement
import json
import pickle

from .utils import touch


class Storage(metaclass=ABCMeta):
    """
    Abstract base class for _all Storages.
    
    A Storage (de)serializes the current state of the database and saves it.
    A Storage has to have implemented read and write methods, close method is non mandatory.
    """

    @abstractmethod
    def read(self):
        """
        Deserealization: Read the last stored state.
        Return None to indicate, that the storage is empty.
        """
        raise NotImplementedError('Base abstract method')

    @abstractmethod
    def write(self, data):
        """
        Serialization: Write current state of DB to storage.
        """
        raise NotImplementedError('Base abstract method')

    def close(self):
        """
        Optional method for closing files, connections etc.
        """
        pass


class MemoryStorage(Storage):
    """
    A bare implementation for Storages. 
    Storing the data in memory.
    """

    def __init__(self):
        super(MemoryStorage, self).__init__()
        self.memory = None

    def read(self):
        return self.memory

    def write(self, data):
        self.memory = data


class PickleStorage(Storage):
    """
    Stores data as pickle file.
    Creates a storage file, if it doesn't exist.

    Note: only Python3 because of Pickle encoding.
    Note: only Python3 because of FileNotFoundError exception.
    """

    def __init__(self, path, **kwargs):
        super(PickleStorage, self).__init__()
        self._kwargs = kwargs
        self._file_path = path
        self.write(None)

    def read(self):
        return pickle.load(open(self._file_path, "rb"))

    def write(self, data):
        pickle.dump(data, open(self._file_path, "wb"))


class XMLStorage(Storage):
    """
    Stores data as XML file.
    Creates a storage file, if it doesn't exist.
    """

    def __init__(self, path, create_dirs=False, **kwargs):
        super(XMLStorage, self).__init__()
        self.kwargs = kwargs
        self._filepath = path

        touch(path, create_dirs=create_dirs)

    def read(self):
        # with open(self._filepath, 'rb') as f:
        #     rawxmlcontent = f.read()
        #     content = xmltodict.parse(rawxmlcontent)
        # return content
        pass  # unable to download packages dicttoxml and xmltodict

    def write(self, data):
        # with open(self._filepath, 'wb') as f:
        #     rawxmldata = dicttoxml(data)
        #     f.write(rawxmldata)
        pass  # unable to download packages dicttoxml and xmltodict


class DBElementEncoder(json.JSONEncoder):
    """
    Overriding json encoder to make DBElement and DBFKElement serializable.
    """
    def default(self, o):
        if isinstance(o, DBFKElement):
            return {
                'fk': {
                    'table': o.table,
                    'fkid': o.fk_id,
                },
                'type': 'fk'
            }
        elif isinstance(o, DBElement):
            return {
                'value': o.value,
                'type': o.type,
            }
        # Let the base class default method raise the TypeError.
        return json.JSONEncoder.default(self, o)


class JSONStorage(Storage):
    """
    Stores data as a JSON file.
    Is a default storage for DB.
    Creates a storage file, if it doesn't exist.

    Note: only Python3.6 because of Unicode.
    """
    
    def __init__(self, path, create_dirs=False, **kwargs):
        super(JSONStorage, self).__init__()
        self._kwargs = kwargs
        self._path = path
        touch(self._path, create_dirs=create_dirs)

    def read(self):
        try:
            with open(self._path) as json_file:
                content = json.load(json_file)
        except:
            return {}
        return content

    def write(self, data):
        with open(self._path, 'w') as json_file:
            json.dump(data, json_file, cls=DBElementEncoder)
