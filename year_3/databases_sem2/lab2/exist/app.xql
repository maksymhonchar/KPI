xquery version "3.1";

module namespace app="localhost:8080/exist/apps/wiki/templates";

import module namespace templates="http://exist-db.org/xquery/templates" ;
import module namespace config="localhost:8080/exist/apps/wiki/config" at "config.xqm";

(:~
 : This is a sample templating function. It will be called by the templating module if
 : it encounters an HTML element with an attribute data-template="app:test" 
 : or class="app:test" (deprecated). The function has to take at least 2 default
 : parameters. Additional parameters will be mapped to matching request or session parameters.
 : 
 : @param $node the HTML node with the attribute which triggered this call
 : @param $model a map containing arbitrary data - used to pass information between template calls
 :)
declare function app:test($node as node(), $model as map(*)) {
    <p>Dummy template output generated by function app:test at {current-dateTime()}. The templating
        function was triggered by the data-template attribute <code>data-template="app:test"</code>.</p>
};





(: PAGES.HTML :)
declare function
app:pages-categories($node as node(), $model as map(*))
{ 
    for $cat in $model("categories")
    
        let $cat_name := <h3>{util:unescape-uri(replace(xs:anyURI($cat), '.+/(.+)$', '$1'), 'UTF-8')}</h3>
        let $pages_links :=
            for $p in xmldb:get-child-resources($cat)
                return
                <li>
                    <a href='{concat('http://localhost:8080/exist/apps/wiki/page.html?pageid=', doc(concat($cat, '/', $p))/page/pageid/text())}'>
                        {doc(concat($cat, '/', $p))/page/title/text()}    
                    </a>
                </li>
        return
            ($cat_name, $pages_links)
};

declare function
app:pages($node as node(), $model as map(*)) {
    let $categories :=
        for $cat in xmldb:get-child-collections("/db/apps/wiki/data")
        return concat("/db/apps/wiki/data/", $cat)
        
    return map { "categories" := $categories }
};
(: PAGES.HTML :)





(: PAGE.HTML :)
declare function
app:page-pageid($node as node(), $model as map(*))
as xs:string
{
    $model("page")/page/pageid
};


declare function
app:page-title($node as node(), $model as map(*))
as xs:string 
{
    $model("page")/page/title
};

declare function
app:page-category($node as node(), $model as map(*))
{
    $model("page")/page/category
};

declare function
app:page-sections($node as node(), $model as map(*))
{
    for $sect in $model("page")/page/sections/section
        return
            <li>
            <h5>{data($sect/@title)}</h5>
            <p>{$sect/text()}</p>
            </li>
};

declare
%templates:default("pageid", 30873244)
function app:page($node as node(), $model as map(*), $pageid as xs:int?)
as map(*) {
    let $page :=
        for $p in collection("/db/apps/wiki/data//?select=*.xml")
        where $p/page/pageid=$pageid
        return $p
        
    return map { "page" := $page }
};
(: PAGE.HTML :)





(: SEARCH.HTML :)
declare
%templates:default("q", "")
function app:search($node as node(), $model as map(*), $q as xs :string?, $mode as xs :string?) {
    if($q = "") then (
        <div/>
    )
    else (
        if($mode = "no_index") then (
            let $starttime as xs:time := util:system-time()
            let $srch_results :=
                for $sect in collection("/db/apps/wiki/data//?select=*.xml")/page/sections/section[contains(text(), $q)]
                    return
                        <div>
                            <h4>from <a href="{concat('http://localhost:8080/exist/apps/wiki/page.html?pageid=', root($sect)//pageid/text())}">{string(root($sect)//title/text())}</a></h4>
                            <p>{string($sect/text())}</p>
                            <br/>
                        </div>
            let $endtime as xs:time := util:system-time()
        return
            <div>
                <h3>Search phrase: "{$q}"</h3>
                <h3>Time elapsed: {seconds-from-duration($endtime - $starttime)}</h3>
                {$srch_results}
            </div>
        )
        else (
            let $starttime as xs:time := util:system-time()            
            let $srch_results :=
                for $sect in collection("/db/apps/wiki/data//?select=*.xml")/page/sections/section[ft:query(., $q)]
                    return
                        <div>
                            <h4>from <a href="{concat('http://localhost:8080/exist/apps/wiki/page.html?pageid=', root($sect)//pageid/text())}">{string(root($sect)//title/text())}</a></h4>
                            <p>{string($sect/text())}</p>
                            <br/>
                        </div>
            let $endtime as xs:time := util:system-time()
            return
                <div>
                    <h3>Search phrase: "{$q}"</h3>
                    <h3>Time elapsed: {seconds-from-duration($endtime - $starttime)}</h3>
                    {$srch_results}
                </div>
        )
    )

};
(: SEARCH.HTML :)




(: ANALYSIS.HTML :)

declare function app:analysis($node as node(), $model as map(*)) {
        let $starttime as xs:time := util:system-time()
    let $documents := collection("/db/apps/wiki/data//?select=*.xml")
    let $all_sections := $documents//section
    let $all_words := ($all_sections ! tokenize(., '[\s]+'))
    let $words := distinct-values($all_words)
    return
        <div>
            <p>Total words: {count($all_words)}</p>
            <p>Total unique words: {count($words)}</p>
            <table border="1">
                <tr>
                 <th>Word</th>
                 <th>Count</th>
                </tr>
                {
                (for $w in $words
                    let $amount := fn:count($all_words[. = $w])
                    order by $amount descending
                    return
                        <tr>
                            <td>{string($w)}</td>
                            <td>{string($amount)}</td>
                        </tr>
                )[position() = 1 to 100]
                }
            </table>
            <p>Time elapsed: {seconds-from-duration(util:system-time() - $starttime)}</p>

        </div>
    
};
(: ANALYSIS.HTML :)
