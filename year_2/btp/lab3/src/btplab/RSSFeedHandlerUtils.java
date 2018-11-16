package btplab;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Map;

public class RSSFeedHandlerUtils {
	
	// return given number of FeedItems based on map.
	public ArrayList<FeedMessage> getFeedMessagesFromTheTopOfMap(Map<String, Integer> map, ArrayList<Feed> allFeeds, int maxSizeOfFeedMessages) {
		ArrayList<FeedMessage> list = new ArrayList<FeedMessage>();
        for (Map.Entry<String, Integer> entry : map.entrySet()) {
        	String name = entry.getKey();
        	// through all feeds
        	for (Feed feed : allFeeds){
        		// through all feedItems
    			for (FeedMessage feedMess : feed.getItems()){
    				if (name == feedMess.title){
    					list.add(feedMess);
    					if (list.size() == maxSizeOfFeedMessages){
    						return list;
    					}
    				}
    			}
        	}
        }
        return list;
    }
	
	// sort Map <String, Integer> by integer value.
	public Map<String, Integer> sortMapByValue(Map<String, Integer> unsortMap) {
        LinkedList<Map.Entry<String, Integer>> list = new LinkedList<Map.Entry<String, Integer>>(unsortMap.entrySet());
        
        Collections.sort(list, 
		new Comparator<Map.Entry<String, Integer>>()
		{
            public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
                return (o1.getValue()).compareTo(o2.getValue());
            }
        } 
        );
        
        Map<String, Integer> sortedMap = new LinkedHashMap<String, Integer>();
        
        for (Map.Entry<String, Integer> entry : list) {
            sortedMap.put(entry.getKey(), entry.getValue());
        }
        return sortedMap;
    }
	
	// get RSS file names from RSS folder.
	public ArrayList<String> getRssFeedNames() {
		File f = new File("rss");
		File[] fLst = f.listFiles();
		
		ArrayList<String> rssFilesLst = new ArrayList<String>();
		for (int i = 0; i < fLst.length; i++) {
			String name = fLst[i].getName();
			rssFilesLst.add(name);
		}
		
		return rssFilesLst;		
	}
	
	// read a file and fill up ArrayList with lines. 
	public ArrayList<String> readFileLines(String filePath) {
		ArrayList<String> lst = new ArrayList<String>();
		try (FileReader reader = new FileReader(filePath)) {
			BufferedReader buffReader = new BufferedReader(reader);
			String curStr = buffReader.readLine();
			while (curStr != null) {
				lst.add(curStr);
				curStr = buffReader.readLine();
			}
			buffReader.close();
		} catch (IOException e) {
			System.err.println(e.getMessage());
		}		
		return lst;
	}
}
