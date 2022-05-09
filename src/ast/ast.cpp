#include "ast.hpp"

ASTGenerator::ASTGenerator(vector<Token> code) : m_code(code) {
    
}

AST gen() {
    AST ret;
    ret.statements = getBody(0).first;
    return ret;
}

pair<vector<Stmt*>, int> getBody(int index) {
    vector<Stmt*> ret;
    int depth = 1;
    while (depth > 0 && index < m_code.size()) {
        if (m_code[index].type == TOKEN_EOF) break;
        if (m_code[index].type == TOKEN_RIGHT_BRACE) break;
        else ret.push_back(getStmt(index));
    }
    return pair<vector<Stmt*>, int>(ret, index);
}

void throwError(string error, int index) {
    cout << error << endl;
    exit(1);
}

sR getStmt(int index) {
    Token first = m_code[index];
    switch (first.type) {
        case TOKEN_COMPONENT_DEF:
            return getComponentDef(index);
        case TOKEN_FUNCTION_DEF:
            return getFunctionDef(index);
        case TOKEN_RETURN:
            return getReturn(index);
        case TOKEN_VARIABLE: {
            if (index < m_code.size() - 1) {
                if (m_code[index+1] == TOKEN_LEFT_PARENTHESIS)
                    return getFunctionCall(index);
                else if (m_code[index + 1] == TOKEN_EQUAL || m_code[index + 1] == TOKEN_SEMICOLON)
                    return getAssignment(index);
                else return getExpr(index);
            }
            throwError("Invalid syntax", index);
        }
        case TOKEN_NUMBER:
            return getExpr(index);
        case TOKEN_LEFT_BRACE:
            return getHtml(index);
        default:
            throwError("Invalid syntax", index);
    }
}

sR getComponentDef(int index) {
    if (index < m_code.size() - 1 && m_code[i+1].type == TOKEN_VARIABLE) {
        sR ret;
        ret.stmt = new StmtComponentDef();
        if (m_code[index+1].type != TOKEN_VARIABLE) throwError("Invalid Component Name.", index);
        pair<vector<Stmt*>, int> body = getBody(i + 3);
        ret.stmt.body = body.first;
        ret.newIndex = body.second;
        return ret;
    } else throwError("Invalid Component Definition.", index);
}

sR getFunctionDef(int index) {
    if (index < m_code.size() - 4 && m_code[i+1].type == TOKEN_VARIABLE) {  
        sR ret;
        ret.stmt = new StmtFunctionDef();
        if (m_code[index+1].type != TOKEN_VARIABLE) throwError("Invalid Function Name.", index);
        ret.name = m_code[index+1].data.tokenValue;
        index += 2;
        while (true) {
            sR stmt = getStmt(index);
            ret.stmt.arguments.push_back(stmt.stmt);
            index = newIndex;
            StmtType argBackT = stmt.stmt.type;
            if (!(argBackT == STMT_FUNCTION_CALL || argBackT == STMT_VARIABLE
                    || argBackT == STMT_STRING || argBackT == STMT_EXPR || argBackT == STMT_HTML))
                throwError("Invalid Function Argument", index);
        }
    } else throwError("Invalid Function Definition.", index);
}
