import os
import urllib.request

import wikitextparser as wtp
from lxml import etree


def get_wiki_xml_page(wiki_url):
    request = urllib.request.Request(wiki_url, headers={'User-Agent': 'Lab2/1.0'})
    url = urllib.request.urlopen(request)
    content = url.read().decode('utf-8')
    return content


def parse_wiki_xml(wiki_xml):
    parsed = dict()
    root = etree.fromstring(wiki_xml)
    page = root.find(".//page")
    cats = page.findall(".//categories/cl")
    parsed['categories'] = list(cat.get('title')[9:] for cat in cats)
    parsed['title'] = page.get('title')
    parsed['pageid'] = page.get('pageid')
    parsed['text'] = page.find(".//extract").text
    return parsed


class Page:
    def __init__(self, pageid):
        self.pageid = pageid
        self.filename = os.path.join(os.path.dirname(__file__), "xml", str(self.pageid) + ".xml")

    def fill_page_with_contents(self, contents):
        tree = etree.parse(self.filename)
        root = tree.getroot()
        root.find(".//title").text = contents['title']
        root.find(".//pageid").text = contents['pageid']
        category = root.find(".//category")
        for cont_category in contents['categories']:
            category.text = cont_category.strip()
            break
        sections = root.find(".//sections")
        undesired_sections = ["See also", "Notes", "External links", "References"]
        for wtp_sect in contents['wtp_sections']:
            if wtp_sect.level < 3 and not (wtp_sect.title.strip() in undesired_sections):
                section = etree.SubElement(sections, 'section')
                section.set('title', wtp_sect.title.strip())
                section.text = wtp_sect.contents
        tree.write(self.filename)

    def xml_page_create(self):
        try:
            wiki_xml = get_wiki_xml_page(
                "https://en.wikipedia.org/w/api.php?action=query&prop=extracts|categories&clshow=!hidden&explaintext="
                "&exsectionformat=wiki&format=xml&pageids=" + str(self.pageid)
            )
            page_contents = parse_wiki_xml(wiki_xml)
            self.create_blank_page()
            wtp_text = wtp.parse(page_contents['text'])
            page_contents['wtp_sections'] = wtp_text.sections
            self.fill_page_with_contents(page_contents)
        except Exception as e:
            print("Error occured while trying to parse the Page with pageid: " + str(self.pageid))
            print(e)
            os.remove(self.filename)

    def create_blank_page(self):
        # if "name" file exists, it will overwrite it
        root = etree.Element('page')
        etree.SubElement(root, 'title')
        etree.SubElement(root, 'pageid')
        etree.SubElement(root, 'category')
        etree.SubElement(root, 'sections')
        tree = etree.ElementTree(root)
        tree.write(self.filename, xml_declaration=True, encoding='UTF-8', method='xml')
