package btplab;

public class FeedMessage {
    public String title;
    public String link;
    public String guid;
    public String description;
    public String date;
    
    public FeedMessage(String title, String description, String link, String author, String guid, String date) {
    	this.title = title;
    	this.description = description;
    	this.link = link;
    	this.guid = guid;
    	this.date = date;
    }
    
    public String shortenToString() {
		String dateToDisplay = this.date == "" ? "No date in RSS source" : this.date;
    	return String.format("\"%s\" \t %s", this.title, dateToDisplay);
    }
   
    @Override
    public String toString() {
    	return String.format( "%s %s %s %s %s", 
    			this.title, 
    			this.description, 
    			this.link, 
    			this.guid, 
    			this.date );
    }
}
