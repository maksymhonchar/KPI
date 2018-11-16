import os
from scrapy import cmdline
from lxml import etree


def football_parse():
    try:
        os.remove("results/football.xml")
    except OSError:
        print("results/football.xml not found")

    cmdline.execute("scrapy crawl football -o results/football.xml -t xml".split())


def football_analysis():
    pages_amount = 0
    images_amount_lst = []
    # Load xml
    root = etree.parse("results/football.xml")
    # Go through each <item>
    for page in root.iterfind(".//item"):
        pages_amount += 1
        for child in page:
            # Find <images>
            if child.tag == "images":
                # Get amount of images on page
                images_amount = len(child)
                images_amount_lst.append(images_amount)
                break
    # If xml has at least one <item>
    if pages_amount != 0:
        print("Total pages: {0}".format(pages_amount))
        for _idx, _images_amount in enumerate(images_amount_lst):
            print('{0} page has {1} {2}.'.format(
                _idx,
                _images_amount,
                'image' if _images_amount==1 else 'images'
            ))
    else:
        print("No pages in XML tree")


def do_football():
    # football_parse()
    football_analysis()


def products_parse():
    try:
        os.remove("results/products.xml")
    except OSError:
        print("results/products.xml not found")

    cmdline.execute("scrapy crawl products -o results/products.xml -t xml".split())


def products_to_xhtml():
    dom = etree.parse("results/products.xml")
    xslt = etree.parse("xslscripts/products.xsl")
    transform = etree.XSLT(xslt)
    result = transform(dom)

    try:
        os.remove("results/products.html")
    except OSError:
        print("results/products.html not found")

    result.write_output("results/products.html")


def do_products():
    # products_parse()
    products_to_xhtml()

do_products()