package btplab;

import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RSSFeedHandler {
	private final String _StopWordsPath = "stopwords.txt";
	private final String _RSSSourcesListPath = "rssNewsList.txt";
	private RSSFeedHandlerUtils _handlerUtils;
	
	public RSSFeedHandler() {
		_handlerUtils = new RSSFeedHandlerUtils();
	}
	
	public ArrayList<Feed> getRSSFeedsFromURL() {
		ArrayList<String> urls = _handlerUtils.readFileLines(_RSSSourcesListPath);
		ArrayList<Feed> feeds = new ArrayList<Feed>();
		
		System.out.println("List of feeds to read from Internet:");
		
		for (int i = 0; i < urls.size(); i++) {	
			RSSFeedParser parser = new RSSFeedParser();
			
			// set up a new URL in parser instance.
			parser.setUrl(urls.get(i));
			
			// get a new feed from URL.
			Feed feed = parser.readFeedFromURL();
			feeds.add(feed);
			System.out.println((i+1) + ". " + feed.shortenToString());
		}
		
		System.out.println(" ");
		
		// return feeds from certain URL.
		return feeds;
	}
	
	public ArrayList<Feed> getRSSFeedsFromPC() {
		RSSFeedParser reader = new RSSFeedParser();
		return reader.readFeedsFromPC(_handlerUtils.getRssFeedNames());
	}
	
	public void displayFeeds(ArrayList<Feed> feeds) {
		for (int i = 0; i < feeds.size(); i++) {
			Feed curFeed = feeds.get(i);
			List<FeedMessage> items = curFeed.getItems();
			System.out.println(curFeed.shortenToString());
			for (int j = 0; j < items.size(); j++) {
				String toPrint = String.format("\t%d. %s", (j+1), items.get(j).shortenToString());
				System.out.println(toPrint);
			}
		}
	}
	
	public void displayFeedItems(ArrayList<FeedMessage> feedItems) {
		if (feedItems == null) {
			System.out.println("FeedItems list is empty");
			return;
		}
		System.out.println("Feed items: ");
		for (FeedMessage itemToPrint : feedItems) {
			System.out.println(itemToPrint.shortenToString());
		}
	}
	
	// delete old feeds. how old - in function parameters. return updated list of feeds.
	public ArrayList<Feed> deleteOldFeeds(long milliSeconds, ArrayList<Feed> allFeeds) throws Exception {
		if (milliSeconds < 0 || allFeeds == null) {
			throw new Exception("Invalid function parameters.");
		}
		
		// search for feed items to remove.
		for (Feed currentFeed : allFeeds) {
			List<FeedMessage> feedItems = currentFeed.getItems(); // current feedItems
			ArrayList<FeedMessage> feedsToRemove = new ArrayList<FeedMessage>();
			for (FeedMessage feedItem : feedItems) {
				String feedItemDateInStr = feedItem.date;
				SimpleDateFormat dateFormat = new SimpleDateFormat("EEE', 'dd' 'MMM' 'yyyy' 'HH:mm:ss' 'Z", Locale.US);
				Date date = dateFormat.parse(feedItemDateInStr, new ParsePosition(0));
				if (date == null) {
					// throw new Exception("Date in FeedItem " + feedItem.link + " has incorrect format");
					continue;
				}
				Date curDate = new Date();
				long diff = curDate.getTime() - date.getTime();
				if (diff > milliSeconds) {
					feedsToRemove.add(feedItem);
				}						
			}
			// delete items from the main feedsList.
			for (FeedMessage itemToRemove : feedsToRemove) {
				currentFeed.deleteItem(itemToRemove);
				System.out.println("Deleted feed " + itemToRemove.shortenToString());
			}
		}
		
		// return updated list of feeds.
		return allFeeds;		
	}
	
	// get feeds by criterion (second lab3 task) from all current feeds.
	public ArrayList<FeedMessage> getFeedItemsByCriterion(ArrayList<Feed> allFeeds) {
		ArrayList<String> stopWords = _handlerUtils.readFileLines(_StopWordsPath);
		
		// get a word from user - a criterion.
		Scanner in = null;
		String word = "";
		try {
			in = new Scanner(System.in);
			while(word == "") {
				System.out.println("Type a word to index feeds:");
				word = in.nextLine();
				for (String stopword : stopWords) {
					if (word == "" || word == null) {
						System.out.println("You entered an empty word.");
						break;
					}
					if (word.equals(stopword)) {
						System.out.println("The word \"" + word +"\" is in the stopWords list.");
						word = "";
						break;
					}
				}
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (in != null) {
				in.close();
			}
		}
		
		// create a map with titleOfFeedItem-UserInputMatchesCount.
		Map<String, Integer> map = new HashMap<String, Integer>();
		for (Feed feed : allFeeds) {
			for (FeedMessage feedItem : feed.getItems()) {
				String str = feedItem.toString();
				Pattern p = Pattern.compile(word); // word - user input.
				Matcher m = p.matcher(str);
				int counter = 0;
				while (m.find()) {
					counter++;
				}
				if (counter != 0) {
					map.put(feedItem.title, counter);
				}				
			}			
		}
		
		// a check if no matches with user input.
		if (map.size() == 0) {
			System.out.println("There are no matches in current feed list with \"" + word + "\"");
			return null; // empty map <"", 0> ?
		}
		
		// sort the map.
		map = _handlerUtils.sortMapByValue(map);
		
		// return 10 top feeds from the sorted map.
		return _handlerUtils.getFeedMessagesFromTheTopOfMap(map, allFeeds, 10);		
	}
	
	// write RSS feeds to PC.
	public void writeRssFeedsToFile(ArrayList<Feed> feeds) {
		for (int i = 0; i < feeds.size(); i++) {
			String rssFileName = String.format("rss\\%s.rss", feeds.get(i).title.trim());
			RSSFeedWriter rssWriter = new RSSFeedWriter(feeds.get(i), rssFileName);
			try {
				rssWriter.write(_handlerUtils.getRssFeedNames());
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}
