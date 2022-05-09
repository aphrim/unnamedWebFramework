#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

//Very simple for now.
//Will have to add ALOT more stmt types and such once work is done on this.

typedef enum {
    STMT_COMPONENT_DEF, STMT_FUNCTION_DEF,
    STMT_FUNCTION_CALL, STMT_ASSIGNMENT,
    STMT_VARIABLE, STMT_STRING,
    STMT_EXPR,
    STMT_RETURN, STMT_HTML,
} StmtType;

typedef struct {
    StmtType type;
} Stmt;

typedef struct {
    vector<Stmt*> statements;        
} AST;

typedef struct StmtComponentDef : public Stmt {
    StmtType type = STMT_COMPONENT_DEF;
    string name;
    vector<Stmt*> body;
}

typedef struct StmtFunctionDef : public Stmt {
    StmtType type = STMT_FUNCTION_DEF;
    string name;
    vector<Stmt*> body;
}

typedef struct StmtFunctionCall : public Stmt {
    StmtType type = STMT_FUNCTION_CALL;
    string name;
    vector<Stmt> arguments;
}

typedef struct StmtAssignment : public Stmt {
    StmtType type = STMT_ASSIGNMENT;
    string name;
    Stmt expr;
}

typedef struct StmtVariable : public Stmt {
    StmtType type = STMT_VARIABLE;
    string name;
}

typedef struct StmtString : public Stmt {
    StmtType type = STMT_STRING;
    string str;
}

typedef struct StmtExpr : public Stmt {
    StmtType type = STMT_EXPR;
    vector<Token> body;
}

typedef struct StmtReturn : public Stmt {
    StmtType type = STMT_RETURN;
    Stmt expr;
}

typedef struct StmtHtml : public Stmt {
    StmtType type = STMT_HTML;
    string name;
    map<string, string> props;
    vector<StmtHtml> children; 
}

class ASTGenerator {
public:
    ASTGenerator(vector<Token> code);
    AST gen();
private:
    vector<Token> m_code;

    struct sR {
        int newIndex;
        Stmt* stmt;
    }

    pair<vector<Stmt*>, int> getBody(int index);
    void throwError(string error, int index);

    sR getStmt(int index);
    
    sR getComponentDef(int index);
    sR getFunctionDef(int index);
    sR getFunctionCall(int index);
    sR getAssignment(int index);
    sR getExpr(int index);
    sR getReturn(int index);
    sR getHtml(int index);
}



