import os
from shutil import copyfile

from lxml import etree

from wikimanager import analyze_category, Page

XML_PATH = os.path.join(os.path.dirname(__file__), "wikimanager", "xml")
ARRANGED_XML_PATH = os.path.join(os.path.dirname(__file__), "wikimanager", "arranged_xml")


def parse_xml_from_wiki():
    if not os.path.exists(XML_PATH):
        os.makedirs(XML_PATH)
    for pageid in analyze_category(691633):
        print("Parsed page")
        Page(pageid).xml_page_create()


def reorganize_xml_by_category():
    if not os.path.exists(ARRANGED_XML_PATH):
        os.makedirs(ARRANGED_XML_PATH)
    for xml_filename in os.listdir(XML_PATH):
        file_path = os.path.join(XML_PATH, xml_filename)
        root = etree.parse(file_path)
        try:
            ct_name = root.xpath("//category/text()")[0].strip()
            category_name = ct_name if ct_name else "nocategory"
        except:
            category_name = "nocategory"
        category_path = os.path.join(ARRANGED_XML_PATH, category_name)
        if not os.path.exists(category_path):
            os.makedirs(category_path)
        copyfile(file_path, os.path.join(category_path, xml_filename))


if __name__ == '__main__':
    # parse_xml_from_wiki()
    reorganize_xml_by_category()
