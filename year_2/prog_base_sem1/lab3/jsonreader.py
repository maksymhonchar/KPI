from os import getcwd
import json


class JsonReader:
    """Class for reading and writing posts from/to .json file."""

    # TODO: setPost, delPost, addPost
    def __init__(self):
        self.json_path = getcwd() + '/data/data.json'

        # Get posts from JSON and save them as a dictionary.
        self._posts_dict = {}
        self._prepPostsDict()

    def getPostsList(self):
        return self._posts_dict['items']

    def getPost(self, post_id):
        to_find = filter(
            lambda post: post['post_id'] == post_id, self._posts_dict['items']
        )
        return list(to_find)

    def getPostCount(self):
        return self._posts_dict['count']

    def getPosts_Item_List(self, item):
        if not isinstance(item, str) or not item:
            return [{'error': 'only strings are allowed as items'}]
        if item not in self.getPostsList()[0]:
            return [{'error': 'no item with name {0}'.format(item)}]
        return [{'id': post['post_id'], item: post[item]} for post in self.getPostsList()]

    def _prepPostsDict(self):
        """Private method. Parse data/data.json file and get an exact dictionary as-is."""
        with open(self.json_path, 'r+', encoding="utf-8") as f:
            tmp = f.read()
            self._posts_dict = json.loads(tmp)

