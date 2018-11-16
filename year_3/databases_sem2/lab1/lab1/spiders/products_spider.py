import scrapy


class ProductsSpider(scrapy.spiders.CrawlSpider):
    name = "products"
    start_urls = ["https://www.moyo.ua/telecommunication/smart/samsung/"]

    def parse(self, response):
        for product in response.css('div.goods_list div.goods_item'):
            yield {
                'title': product.css('a.goods_title::text').extract_first(),
                'src':   product.css('a.goods_title::attr(href)').extract_first(),
                'price': product.css('div.vfixed-container div.goodsprice-col div.goodsprice-amount span::text').extract_first(),
                'rate':  product.css('div.rate_block div.rote_namber span::text').extract_first(),
                'img': response.urljoin(product.css('a.goods_image::attr(data-imagesrc)').extract_first())
            }

        next_page = response.css('div.pagination a::attr(href)').extract()
        if next_page is not None and int(next_page[0][-1]) <= 2:  # ?page=2
            yield scrapy.Request(response.urljoin(next_page[0]), callback=self.parse)
