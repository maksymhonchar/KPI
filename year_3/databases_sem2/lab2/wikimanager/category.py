import urllib.request

from lxml import etree

wiki_req_path = 'https://en.wikipedia.org/w/api.php?action=query&list=categorymembers&cmlimit=600&format=xml&cmtype={0}'


def get_category_item(category_url):
    request = urllib.request.Request(category_url, headers={'User-Agent': 'Lab2/1.0'})
    url = urllib.request.urlopen(request)
    content = url.read().decode('utf-8')
    return content


def get_category_subcategories(pageid):
    req_path = wiki_req_path.format("subcat")
    req_path += '&cmpageid=' + str(pageid)
    wiki_xml_content = get_category_item(req_path)
    root = etree.fromstring(wiki_xml_content)
    items = root.findall('.//categorymembers/cm')
    catsubcats = list(item.get('pageid') for item in items)
    return catsubcats


def get_category_pages(pageid):
    req_path = wiki_req_path.format("page")
    req_path += '&cmpageid=' + str(pageid)
    wiki_xml_content = get_category_item(req_path)
    root = etree.fromstring(wiki_xml_content)
    items = root.findall('.//categorymembers/cm')
    catpages = list(item.get('pageid') for item in items)
    return catpages


def analyze_category(category_pageid):
    # Pages. Its Subcategories. Theirs pages.
    pages = get_category_pages(category_pageid)
    subcats = get_category_subcategories(category_pageid)[:10]
    for subcat_pageid in subcats:
        pages.extend(get_category_pages(subcat_pageid))
    return pages
