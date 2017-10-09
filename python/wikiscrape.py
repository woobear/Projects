#Robert Wooner
import os 
import sqlite3
import sys
import urllib.parse
import xml.etree.ElementTree as ET
import requests


###################
#  Wiki URL vars  #
###################

wiki = "https://en.wikipedia.org/w/api.php?"
summaries = "action=query&format=xml&prop=extracts&explaintext&exintro&titles="
category_member = "action=query&list=categorymembers&format=xml&cmlimit=500&cmtitle=Category:"
subject_categorys = "format=xml&action=query&prop=categories&cllimit=500&titles="
images = "action=query&prop=pageimages&pithumbsize=1000&format=xml&titles="
URlS= "format=xml&action=opensearch&search="

###################
#  Progress Bar   #
###################

def progress_bar(value, endvalue, bar_length=60):
    percent = float(value) / endvalue
    arrow = '-' * int(round(percent * bar_length)-1) + '>'
    spaces = ' ' * (bar_length - len(arrow))
    sys.stdout.write("\r\t[{0}] {1}%".format(arrow + spaces, int(round(percent * 100))))
    sys.stdout.flush()

########################################################################
#                           *SEARCH_CATS*                              #
# searchs for categories in any subject                                # 
# filters out any category that have more then three words             #
# to avoid useless categories that don't purtain to my topic           #
########################################################################

def search_cats(topic): 
    cat_num = 0
    search_request = requests.get(wiki+subject_categorys+topic)
    root = ET.fromstring(search_request.content)
    children = root.findall('query/pages/page/categories/cl')
    categories = [] 
    for child in children:
        raw_categories = child.attrib['title']
        if len(raw_categories.split()) <= 3:
            categories.append(raw_categories[9:])
            cat_num = cat_num + 1
        else:
            continue
    return categories, cat_num

########################################################################
#                      *PAGE_TITLE_SEARCH*                           #
# searchs for the titles of subcategories                              #
# gets rid of and "Category:" tag                                      #
########################################################################

def page_title_search(category):
    category_member_URL = requests.get(wiki+category_member+category)
    root = ET.fromstring(category_member_URL.content)
    children = root.findall('query/categorymembers/cm')
    sub_cats = []
    page_count = 0
    for child in children:
        if "Category:" in child.attrib['title']:
            continue
        elif "File:" in child.attrib['title']:
            continue
        else:
            sub_cats.append(child.attrib['title'])
            page_count = page_count + 1
    return sub_cats,page_count

########################################################################
#                      *SUMMARY_SCRAPE*                                #
# grabs summaries for each page                                        #
########################################################################

def summary_scrape(page_list):
    summs = []
    sum_count = 0
    for i,titles in enumerate(page_list):
        progress_bar(i,len(page_list)-1)
        search_request = requests.get(wiki+summaries+urllib.parse.quote(titles))
        root = ET.fromstring(search_request.content)
        pages = root.find('query/pages/page/extract')
        summs.append(pages.text)
        sum_count = sum_count + 1
    return summs, sum_count

########################################################################
#                      *GET_PAGE_TITLES*                               #
# gets all the page titles and puts them in an array                   #
########################################################################

def get_page_titles(categories):
    page_list = []
    page_num_array = []
    for index, category in enumerate(categories):
        progress_bar(index,len(categories)-1)
        pages,page_count = page_title_search(category)
        #puts pages in an array
        page_list = page_list + pages
        # keeps track of how many pages per category
        page_num_array.append(page_count)
    return page_list, page_num_array

def get_urls(pages):
    urls = []
    for i in pages:
        urls.append("https://en.wikipedia.org/wiki/"+i)
    return urls




    
def main():
    print("WARNING: somethings you search may need an underscore instead of a space")
    print("What would you like to read about?")
    topic = input('>')
    categories, cat_num  = search_cats(topic)
    print("Categorys: %d" % (cat_num))
    page_num_array = []
    summary = []

    num_of_pages = 0
    page_list, page_num_array = get_page_titles(categories)
    urls = get_urls(page_list)
    print()
    print("Categories are...")
    print(categories)
    print("The numbers of pages in each category are %s" % (page_num_array))
    num_of_pages = len(page_list)
    print("Number of pages is %d" % (num_of_pages))


    summary, sum_count = summary_scrape(page_list)
    print()
    print(sum_count)
    
    #enter things into database
    connection = sqlite3.connect(topic+'.db')
    cursor = connection.cursor()
    
    
    total = 0
    #puts the different list into one list to put in the SQLite DB 
    #also puts the new list into the DB
    for i, count in enumerate(page_num_array):
        wiki_tuples = []
        for x in range(count):
            wiki_tuples.append((page_list[x + total], summary[x + total], urls[x + total]))
        cursor.execute('CREATE TABLE if not exists ['+categories[i]+'] (title ,summary,urls)' )
        cursor.executemany('INSERT INTO ['+categories[i]+'] VALUES (?,?,?)' ,wiki_tuples)
        total += count
    connection.commit()
    connection.close()


if __name__ == "__main__":
    main()
