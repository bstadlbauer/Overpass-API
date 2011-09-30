#ifndef DE__OSM3S___OVERPASS_API__STATEMENTS__STATEMENT_H
#define DE__OSM3S___OVERPASS_API__STATEMENTS__STATEMENT_H

#include <map>
#include <set>
#include <vector>

#include "../core/datatypes.h"
#include "../core/settings.h"
#include "../dispatch/resource_manager.h"
#include "../osm-backend/area_updater.h"
#include "../osm-backend/stopwatch.h"

using namespace std;

class Query_Constraint
{
  public:
    virtual bool collect(Resource_Manager& rman, Set& into,
			 int type, const vector< uint32 >& ids) { return false; }
    virtual bool get_ranges
        (Resource_Manager& rman, int type,
	 set< pair< Uint32_Index, Uint32_Index > >& ranges)
      { return false; }
    virtual void filter(Resource_Manager& rman, Set& into) = 0;
    virtual ~Query_Constraint() {}
};

/**
 * The base class for all statements
 */
class Statement
{
  public:
    Statement(int line_number_) : line_number(line_number_) {}
    
    virtual void set_attributes(const char **attr) = 0;
    virtual void add_statement(Statement* statement, string text);
    virtual void add_final_text(string text);
    virtual string get_name() const = 0;
    virtual string get_result_name() const = 0;
    virtual void forecast() = 0;
    virtual void execute(Resource_Manager& rman) = 0;

    // May return 0. The ownership of the Query_Constraint remains at the called
    // object.
    virtual Query_Constraint* get_query_constraint() { return 0; }
    
    virtual ~Statement() {}
    
    int get_line_number() const { return line_number; }
    int get_startpos() const { return startpos; }
    void set_startpos(int pos) { startpos = pos; }
    int get_endpos() const { return endpos; }
    void set_endpos(int pos) { endpos = pos; }
    int get_tagendpos() const { return tagendpos; }
    void set_tagendpos(int pos) { tagendpos = pos; }
    
    void display_full();
    void display_starttag();
        
    static Statement* create_statement(string element, int line_number);
    static void set_error_output(Error_Output* error_output_)
    {
      error_output = error_output_;
      Stopwatch::set_error_output(error_output);
    }
    
    const static int NODE = 1;
    const static int WAY = 2;
    const static int RELATION = 3;
    
    Stopwatch stopwatch;
  
  private:
    static Error_Output* error_output;
    
    int line_number;
    int startpos, endpos, tagendpos;
        
  protected:
    void eval_cstr_array
        (string element, map< string, string >& attributes, const char **attr);
    void assure_no_text(string text, string name);
    void substatement_error(string parent, Statement* child);
    
    void add_static_error(string error);
    void add_static_remark(string remark);

    void runtime_remark(string error);
};

#endif
