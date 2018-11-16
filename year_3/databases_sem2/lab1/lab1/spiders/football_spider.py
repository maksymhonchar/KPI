import scrapy


class FootballSpider(scrapy.spiders.CrawlSpider):
    name = "football"
    start_urls = [
        "http://football.ua/newsarc/",
        "http://football.ua/newsarc/page2.html"
    ]

    def parse(self, response):
        for text in response.xpath("//article[@class='author-article']"):
            yield {
                'url': response.url,
                'fragments': text.xpath(".//p/text()").extract(),
                'images': text.xpath(".//img/@src").extract(),
            }

        for a in response.xpath("//ul[@class='archive-list']").xpath(".//a[@class='intro-text']"):
            yield response.follow(a, callback=self.parse)
