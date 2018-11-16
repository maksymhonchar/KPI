package btplab;

import java.util.ArrayList;

public class Main {
	
	public static void main(String[] args) throws Exception {
		// lab3 part 1.
		RSSFeedHandler handler = new RSSFeedHandler();
		ArrayList<Feed> feeds;
		
		// get RSS news from the Internet.
		feeds = handler.getRSSFeedsFromURL();
		
		// write news from Internet to PC.
		handler.writeRssFeedsToFile(feeds);
		
		// read RSS news from PC.
		feeds = handler.getRSSFeedsFromPC();
		
		// display news from PC.
		handler.displayFeeds(feeds);
		
		System.out.println("");		
		
		System.out.println("");
		
		// lab3 part 2.
		
		// delete the RSS news that are saved more than given number
		long time = 1 * 24 * 60 * 60 * 1000; // 24h
		feeds = handler.deleteOldFeeds(time, feeds);
		
		// write updated list of feeds to PC.
		handler.writeRssFeedsToFile(feeds);
		
		System.out.println("");
		
		// display updated list of feeds.
		handler.displayFeeds(feeds);
		
		System.out.println("");
		
		System.out.println("");
		
		// lab3 part 2.2
		
		// get 10 RSS news by criterion, written by user.
		ArrayList<FeedMessage> feedItemsFromUserCriterion = handler.getFeedItemsByCriterion(feeds);
		
		// display array of feedItems.
		handler.displayFeedItems(feedItemsFromUserCriterion);
		
		// end of the program.
		System.out.println("End of the program.");
		
	}
}
