package btplab;

import static org.junit.Assert.*;
import static org.mockito.Mockito.*;

import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

public class Tests {
	RSSFeedHandler handler;
	RSSFeedParser parser;
	RSSFeedWriter writer;
	
	@Before
	public void setup() {
		handler = mock(RSSFeedHandler.class);
		parser = mock(RSSFeedParser.class);
		writer = mock(RSSFeedWriter.class);
	}
	
	@Test
	public void ifReaderIsRSSFeedReader() {
		// check types for mock objects.
		assertTrue(parser instanceof RSSFeedParser);
	}
	
	@Test
	public void ifHandlerIsRSSFeedHandler() {
		// check types for mock objects.
		assertTrue(handler instanceof RSSFeedHandler);
	}
	
	@Test
	public void ifWriterIsRSSFeedWriter() {
		// check types for mock objects.
		assertTrue(writer instanceof RSSFeedWriter);
	}
	
	@Test
	public void compareInternetAndLocalFeeds() {
		// Get feeds from the Internet.
		ArrayList<Feed> feedsFromInternet = handler.getRSSFeedsFromURL();
		// Save feeds to locally.
		handler.writeRssFeedsToFile(feedsFromInternet);
		// Get feeds from local storage.
		ArrayList<Feed> feedsFromPC = handler.getRSSFeedsFromPC();
		
		assertEquals(feedsFromInternet, feedsFromPC);		
	}
	
	@Test
	public void test() throws Exception {
		handler.deleteOldFeeds(0, null);
		handler.getRSSFeedsFromURL();
		handler.displayFeedItems(null);
		handler.displayFeeds(null);
		handler.writeRssFeedsToFile(null);
		handler.getRSSFeedsFromPC();
		handler.getFeedItemsByCriterion(null);
		
		// verify if these methods have executed (!) once.
		// verify with dummy objects.
		verify(handler).deleteOldFeeds(0, null);
		verify(handler).getRSSFeedsFromURL();
		verify(handler).displayFeedItems(null);
		verify(handler).displayFeeds(null);
		verify(handler).writeRssFeedsToFile(null);
		verify(handler).getRSSFeedsFromPC();
		verify(handler).getFeedItemsByCriterion(null);
	}
}













