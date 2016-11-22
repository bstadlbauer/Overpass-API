/** Copyright 2008, 2009, 2010, 2011, 2012 Roland Olbricht
*
* This file is part of Overpass_API.
*
* Overpass_API is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Overpass_API is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Overpass_API.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DE__OSM3S___OVERPASS_API__STATEMENTS__SET_TAG_H
#define DE__OSM3S___OVERPASS_API__STATEMENTS__SET_TAG_H


#include "../data/tag_store.h"
#include "../data/utils.h"
#include "evaluator.h"
#include "statement.h"

#include <map>
#include <string>
#include <vector>


class Set_Tag_Statement : public Statement
{
public:
  Set_Tag_Statement(int line_number_, const map< string, string >& input_attributes,
                   Parsed_Query& global_settings);
  virtual string get_name() const { return "set-tag"; }
  virtual string get_result_name() const { return ""; }
  virtual void add_statement(Statement* statement, string text);
  virtual void execute(Resource_Manager& rman) {}
  virtual ~Set_Tag_Statement() {}
    
  static Generic_Statement_Maker< Set_Tag_Statement > statement_maker;

  std::string eval(const std::string* key = 0);
  std::string eval(const Node_Skeleton* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
  std::string eval(const Attic< Node_Skeleton >* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
  std::string eval(const Way_Skeleton* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
  std::string eval(const Attic< Way_Skeleton >* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
  std::string eval(const Relation_Skeleton* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
  std::string eval(const Attic< Relation_Skeleton >* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
  std::string eval(const Area_Skeleton* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
  std::string eval(const Derived_Skeleton* elem,
      const std::vector< std::pair< std::string, std::string > >* tags, const std::string* key = 0);
      
  void prefetch(const Set_With_Context& set);
  
  std::pair< std::vector< Set_Usage >, uint > used_sets() const;
  
  std::vector< std::string > used_tags() const;
   
  const std::string* get_key() const { return input != "" ? 0 : &keys.front(); }
  bool has_value() const { return tag_value; }
  bool should_set_id() const { return set_id; }
  
  void clear();
    
private:
  std::string input;
  std::vector< std::string > keys;
  bool set_id;
  Evaluator* tag_value;
};


#endif
