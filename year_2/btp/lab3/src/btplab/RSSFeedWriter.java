package btplab;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.DirectoryNotEmptyException;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Path;
import java.util.ArrayList;

import javax.xml.stream.XMLEventFactory;
import javax.xml.stream.XMLEventWriter;
import javax.xml.stream.XMLOutputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartDocument;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

public class RSSFeedWriter {
	private String _outputFile;
	private Feed _rssFeed;
	
	public RSSFeedWriter(Feed rssFeed, String outputFile) {
		_outputFile = outputFile;
		_rssFeed = rssFeed;
	}
	
	public void write(ArrayList<String> fileNamesToDelete) throws Exception {
		for (int i = 0; i < fileNamesToDelete.size(); i++) {
			Path path = FileSystems.getDefault().getPath("rss", fileNamesToDelete.get(i));
			this.deleteFile(path);
		}
		
		XMLOutputFactory outputFactory = XMLOutputFactory.newInstance();
		XMLEventWriter eventWriter = outputFactory.createXMLEventWriter(new FileOutputStream(_outputFile));
		
		XMLEventFactory eventFactory = XMLEventFactory.newInstance();
		XMLEvent end = eventFactory.createDTD("\n");
		
		// root of the XML document.
        StartDocument startDocument = eventFactory.createStartDocument("Windows-1251", "1.0");        
        eventWriter.add(startDocument);
        eventWriter.add(end);
        
        // root of the rss feeds.
        StartElement rssStart = eventFactory.createStartElement("", "", "rss");
        
        eventWriter.add(rssStart);
        eventWriter.add(eventFactory.createAttribute("version", "2.0"));
        eventWriter.add(end);
        
        eventWriter.add(eventFactory.createStartElement("", "", "channel"));
        eventWriter.add(end);

    	// fill up info about feed.
        createNode(eventWriter, "title", _rssFeed.title);
        createNode(eventWriter, "link", _rssFeed.link);
        createNode(eventWriter, "description", _rssFeed.description);
        createNode(eventWriter, "language", _rssFeed.language);
        
        eventWriter.add(end);
		
        // add feedItems for each feed.
        for (FeedMessage entry : _rssFeed.getItems()) {
            eventWriter.add(eventFactory.createStartElement("", "", "item"));
            eventWriter.add(end);
            
            // add nodes about certain feedItem.
            createNode(eventWriter, "title", entry.title);
            createNode(eventWriter, "description", entry.description);
            createNode(eventWriter, "link", entry.link);
            createNode(eventWriter, "guid", entry.guid);
            createNode(eventWriter, "pubDate", entry.date);
            
            eventWriter.add(eventFactory.createEndElement("", "", "item"));
            eventWriter.add(end);
            eventWriter.add(end);
        }
        
        // finish feed element.
        eventWriter.add(end);
        
        eventWriter.add(eventFactory.createEndElement("", "", "channel"));
        eventWriter.add(end);
        
        eventWriter.add(eventFactory.createEndElement("", "", "rss"));
        eventWriter.add(end);
        
        // finish document.
        eventWriter.add(eventFactory.createEndDocument());
        
        // close event writer stream.
        eventWriter.close();		
	}
	
	public void deleteFile(Path path) {
		try {
			Files.delete(path);
		} catch (NoSuchFileException e) {
			System.err.format("%s: no such file or directory.\n", path);
		} catch (DirectoryNotEmptyException e) {
			System.err.format("%s is not empty.\n", path);
		} catch (IOException e) {
			// if a file already exists - pass.
		}
	}
	
	private void createNode(XMLEventWriter eventWriter, String name, String value) throws XMLStreamException {
        XMLEventFactory eventFactory = XMLEventFactory.newInstance();
        XMLEvent end = eventFactory.createDTD("\n");
        XMLEvent tab = eventFactory.createDTD("\t");
        
        StartElement sElement = eventFactory.createStartElement("", "", name);
        eventWriter.add(tab);
        eventWriter.add(sElement);
        
        Characters characters = eventFactory.createCharacters(value);
        eventWriter.add(characters);
        
        EndElement eElement = eventFactory.createEndElement("", "", name);
        eventWriter.add(eElement);
        eventWriter.add(end);
	}	
}
