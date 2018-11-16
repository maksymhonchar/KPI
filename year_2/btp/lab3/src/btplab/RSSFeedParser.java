package btplab;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.XMLEvent;

public class RSSFeedParser {
	private URL _url;
	
	public void setUrl(String feedUrl) throws RuntimeException {
		try {
			_url = new URL(feedUrl);
		} catch (MalformedURLException e) {
			throw new RuntimeException(e);
		}
	}
	
	public Feed readFeedFromURL() {
		InputStream in = this.openUrlConnection();
		return this.readFeed(in);
	}
	
	public ArrayList<Feed> readFeedsFromPC(ArrayList<String> rssNames) throws RuntimeException {
		ArrayList<Feed> feeds = new ArrayList<Feed>();
		for (int i = 0; i < rssNames.size(); i++) {
			String rssFilePath = "rss\\" + rssNames.get(i);
			try {
				InputStream in = new FileInputStream(new File(rssFilePath));
				feeds.add(this.readFeed(in));
			} catch (FileNotFoundException e) {
				String errorMsg = String.format("File %s not found.\n", rssFilePath);
				throw new RuntimeException(errorMsg + e);
			}
		}		
		return feeds;		
	}
	
	private Feed readFeed(InputStream in) throws RuntimeException {
		Feed feed = null;
		try {
			boolean isFeedHeader = true;
            
			String description = "";
            String title = "";
            String link = "";
            String language = "";
            String author = "";
            String date = "";
            String guid = "";
            
            XMLInputFactory inputFactory = XMLInputFactory.newInstance();
            XMLEventReader eventReader = inputFactory.createXMLEventReader(in);            
            
            while (eventReader.hasNext()) {
				XMLEvent event = eventReader.nextEvent();
				if (event.isStartElement()) {
					// get tag name.
					String localPart = event.asStartElement().getName().getLocalPart();
					
					switch (localPart) {					
					case "item":
						if (isFeedHeader) {
							isFeedHeader = false;
							// start to parse the whole new RSS feed from XML.
							feed = new Feed(title, link, description, language, date);
						}
						event = eventReader.nextEvent();
						break;
					
					case "title":
						title = getEventData(event, eventReader);
						break;
					case "description":
						description = getEventData(event, eventReader);
						break;
					case "link":
						link = getEventData(event, eventReader);
						break;
					case "guid":
						guid = getEventData(event, eventReader);
						break;
					case "language":
						language = getEventData(event, eventReader);
						break;
					case "author":
						author = getEventData(event, eventReader);
						break;
					case "pubDate":
						date = getEventData(event, eventReader);
						break;	
					case "date": // if pubDate does not exist in current XML format.
						date = getEventData(event, eventReader);
						break;
					}
				} else if(event.isEndElement()) {
					if (event.asEndElement().getName().getLocalPart() == "item") {
						FeedMessage item = new FeedMessage(title, description, link, author, guid, date);
						feed.getItems().add(item);
						event = eventReader.nextEvent();
						continue;
					}					
				}            	
			}            
		} catch (XMLStreamException e) {
			throw new RuntimeException(e);
		}
		return feed;
	}
	
	private String getEventData(XMLEvent event, XMLEventReader eventReader) throws XMLStreamException {
		String result = "";
		event = eventReader.nextEvent();
		if (event instanceof Characters) {
			result = event.asCharacters().getData();			
		}
		return result;	
	}
	
	private InputStream openUrlConnection() throws RuntimeException {
		try {
			return _url.openStream();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
}
