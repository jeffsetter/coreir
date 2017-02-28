#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include "namespace.hpp"
#include "typecache.hpp"
#include "types.hpp"
#include <string>
#include "enums.hpp"
#include <unordered_set>
#include <vector>

using namespace std;
class CoreIRContext {
  Namespace* global;
  map<string,Namespace*> libs;
  TypeCache* cache;
  
  bool err;
  string errmsg;
 
  //Memory management
  vector<GenArg*> genargList;
  vector<GenArgs*> genargsList;
  unordered_set<Generator*> generatorSet;
  unordered_set<Module*> moduleSet;
  
  public :
    CoreIRContext();
    ~CoreIRContext();
    Namespace* getGlobal() {return global;}
    void newerror() { err = true; errmsg = errmsg + "\n\nERROR: ";}
    void error(string s) { errmsg = errmsg + "\t" + s + "\n";}
    bool haserror() { return err; }
    void printerror() { cout << errmsg << endl;}
    void registerLib(Namespace* lib);
    Type* Any();
    Type* BitIn();
    Type* BitOut();
    Type* Array(uint n, Type* t);
    Type* Record(RecordParams rp);
    Type* TypeGenInst(TypeGen* tgd, GenArgs* args);

    GenArg* GInt(int i);
    GenArg* GString(string s);
    GenArg* GType(Type* t);
    int toInt(GenArg* g);
    string toString(GenArg* g);
    Type* toType(GenArg* g);
    GenArgs* newGenArgs(uint len, vector<GenArg*> args);   

    //TODO have an interface for GenArgs
  
    Type* Flip(Type* t);
    Generator* newGeneratorDecl(string name, ArgKinds kinds, TypeGen* tg);
    Module* newModuleDecl(string name, Type* t);



};

CoreIRContext* newContext();
void deleteContext(CoreIRContext* m);


#endif //CONTEXT_HPP_
