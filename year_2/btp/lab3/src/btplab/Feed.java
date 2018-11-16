package btplab;

import java.util.ArrayList;
import java.util.List;

public class Feed {
	
	public String title;
	public String link;
	public String description;
	public String language;
	
	private List<FeedMessage> _messages = new ArrayList<FeedMessage>();
	
	public Feed(String title, String link, String description, String language, String date) {
        this.title = title;
        this.link = link;
        this.description = description;
        this.language = language;
	}
	
	public List<FeedMessage> getItems() {
		return _messages;
	}
	
	public boolean deleteItem(FeedMessage item) {
		return _messages.remove(item);
	}
	
	public int getItemsCount() {
		return _messages.size();
	}
	
	public String shortenToString() {
		return String.format("Feed \"%s\"", this.title);
	}
	
	@Override
	public String toString() {
		return String.format( "%s %s %s %s", 
				this.title,
				this.link,
				this.description,
				this.language );
	}
}
