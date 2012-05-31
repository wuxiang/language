#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/tokenizer.hpp>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>

using boost::multi_index_container;
using namespace boost::multi_index;


class obj
{
public:
    obj(): m_size(0)
    {
    }

    obj(const std::string& name, const size_t& num): m_name(name), m_size(num)
    {
    }

    ~obj()
    {
    }

    void print()
    {
        std::cout << "obj-name: " << m_name << ", size: " << m_size << std::endl;
    }

private:
    std::string  m_name;
    size_t       m_size;
};

typedef multi_index_container<
    std::string,
    indexed_by<
            sequenced<>,
            ordered_non_unique<identity<std::string> >
              >
     > text_container;

/* ordered index */

typedef nth_index<text_container,1>::type ordered_text;

typedef boost::tokenizer<boost::char_separator<char> > text_tokenizer;


int main()
{
    std::string text=
        "Alice was beginning to get very tired of sitting by her sister on the "
        "bank, and of having nothing to do: once or twice she had peeped into the "
        "book her sister was reading, but it had no pictures or conversations in "
        "it, 'and what is the use of a book,' thought Alice 'without pictures or "
        "conversation?'";

    /* feed the text into the container */

    text_container tc;
    text_tokenizer tok(text,boost::char_separator<char>(" \t\n.,;:!?'\"-"));
    std::copy(tok.begin(),tok.end(),std::back_inserter(tc));

    /* list all words in alphabetical order along with their number
     *    * of occurrences
     *       */

    std::cout << "=========================1=====================" << std::endl;
    ordered_text& ot=get<1>(tc);
    for(ordered_text::iterator it=ot.begin();it!=ot.end();){
        std::cout<<std::left<<std::setw(14)<<*it<<":";  /* print the word */
        ordered_text::iterator it2=ot.upper_bound(*it); /* jump to next   */
        std::cout<<std::right<<std::setw(3)   /* and compute the distance */
            <<std::distance(it,it2)<<" times"<<std::endl;
        it=it2;
    }
    std::cout << "=========================end 1=====================" << std::endl;

    /* reverse the text and print it out */

    std::cout << "=========================2=====================" << std::endl;
    tc.reverse();
    std::cout<<std::endl;
    std::copy( tc.begin(),tc.end(),std::ostream_iterator<std::string>(std::cout," "));
    std::cout<<std::endl;
    tc.reverse(); /* undo */
    std::cout << "=========================end 2=====================" << std::endl;

    /* delete most common English words and print the result */

    std::string common_words[]=
    {"the","of","and","a","to","in","is","you","that","it",
        "he","for","was","on","are","as","with","his","they","at"};

    for(std::size_t n=0;n<sizeof(common_words)/sizeof(common_words[0]);++n){
        ot.erase(common_words[n]);
    }
    std::cout << "=========================3=====================" << std::endl;
    std::cout<<std::endl;
    std::copy( tc.begin(),tc.end(),std::ostream_iterator<std::string>(std::cout," "));
    std::cout<<std::endl;
    std::cout << "=========================end 3=====================" << std::endl;

    return 0;
}

