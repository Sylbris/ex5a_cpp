/**
 * Test file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-05
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "doctest.h"
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

TEST_CASE("Basic Operations"){
    OrgChart organization;
    //CHECK adding without root.
    CHECK_THROWS(organization.add_sub("CTO", "CEO"));
    organization.add_root("CEO");
    //Try adding.
    CHECK_THROWS(organization.add_sub("CTO", "CEO"));
    CHECK_NOTHROW(organization.add_sub("CEO", "EMP"));

    //Change root.
    organization.add_root("CFO");
    CHECK_THROWS(organization.add_sub("CEO", "CTO"));
    CHECK_NOTHROW(organization.add_sub("CFO", "CTO"));

    //Our organization should like this now.
    vector<string> test_vector{"CFO", "EMP", "CTO"};
    int i = 0;
    for (auto element : organization){
        CHECK_EQ(test_vector[(size_t)i++], element);
    }

    //Try full length build.
    OrgChart numbers;
    CHECK_NOTHROW(numbers.add_root("1")
      .add_sub("1", "2")
      .add_sub("1", "3")
      .add_sub("1", "4")
      .add_sub("2", "5")
      .add_sub("4", "6"));

}
/**
 * @brief Check our different iterators.
 * 
 */
TEST_CASE("Check different iterators"){
    OrgChart amazon;
    CHECK_NOTHROW(amazon.add_root("JEFF_BEZOS")
      .add_sub("JEFF_BEZOS", "DAN_DAVIDOV")
      .add_sub("JEFF_BEZOS", "BRIAN_OLVANSKY")
      .add_sub("JEFF_BEZOS", "ALBERT_CHANG")
      .add_sub("DAN_DAVIDOV", "DAN_DAVIDOV_HELP")
      .add_sub("ALBERT_CHANG", "ALBERT_CHANG_Jr"));
    
    //each node has exactly one child.
    OrgChart family_business;
    CHECK_NOTHROW(family_business.add_root("FATHER")
      .add_sub("FATHER", "SON").add_sub("SON", "GRANDCHILD")
      .add_sub("GRANDCHILD", "GRANDGRANDCHILD"));

    /**
     * @brief We perform order check & we check the * function in the iterator.
     * 
     */
    SUBCASE("LEVEL ORDER"){
        vector<string> amazon_bfs_vector{"JEFF_BEZOS", "DAN_DAVIDOV",
         "BRIAN_OLVANSKY", "ALBERT_CHANG", "DAN_DAVIDOV_HELP", "ALBERT_CHANG_Jr"};
        size_t i = 0;
        for (auto it = amazon.begin_level_order(); it != amazon.end_level_order(); ++it){
            CHECK_EQ((*it) , amazon_bfs_vector[i++]);
        }
        i = 0;
        //We will return the same as above.
        for (auto element : amazon){
             CHECK_EQ(element , amazon_bfs_vector[i++]);
        }

        vector<string> family{"FATHER", "SON", "GRANDCHILD", "GRANDGRANDCHILD"};
        i = 0;
        for (auto it = family_business.begin_level_order(); it != family_business.end_level_order(); ++it){
            CHECK_EQ((*it) , family[i++]);
        }
        i = 0;
        //We will return the same as above.
        for (auto element : family_business){
             CHECK_EQ(element , family[i++]);
        }
    }
    ////////////////REVERSE ORDER///////////////////////////////////////
    SUBCASE("REVERSE ORDER"){
        vector<string> rbfs_vector{"JEFF_BEZOS", "DAN_DAVIDOV",
         "BRIAN_OLVANSKY", "ALBERT_CHANG", "DAN_DAVIDOV_HELP", "ALBERT_CHANG_Jr"};

        vector<string> family{"GRANDGRANDCHILD", "GRANDCHILD", "SON", "FATHER"};
        size_t i = 0;
        for (auto it = amazon.begin_level_order(); it != amazon.end_level_order(); ++it){
            CHECK_EQ((*it) , rbfs_vector[i++]);
        }
        i = 0;
        //CHECK_FAMILY
        for (auto it = family_business.begin_reverse_order(); it != family_business.reverse_order(); ++it){
            CHECK_EQ((*it) , family[i++]);
        } 
    }
    ////////////////PREORDER///////////////////////////////////////
    SUBCASE("PREORDER"){
        vector<string> dfs_vector{"JEFF_BEZOS", "DAN_DAVIDOV",
         "BRIAN_OLVANSKY", "ALBERT_CHANG", "DAN_DAVIDOV_HELP", "ALBERT_CHANG_Jr"};
        size_t i = 0;
        for (auto it = amazon.begin_level_order(); it != amazon.end_level_order(); ++it){
            CHECK_EQ((*it) , dfs_vector[i++]);
        }
        vector<string> family{"FATHER", "SON", "GRANDCHILD", "GRANDGRANDCHILD"};
        i = 0;
        for (auto it = family_business.begin_preorder(); it != family_business.end_preorder(); ++it){
            CHECK_EQ((*it) , family[i++]);
        }
    }
    //////////////////////////////////////////
}
