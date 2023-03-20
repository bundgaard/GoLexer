#pragma once

#include <vector>

/*
f := &ast.File{
		Doc:       doc,
		Package:   pos,
		Name:      ident,
		Decls:     decls,
		FileStart: token.Pos(p.file.Base()),
		FileEnd:   token.Pos(p.file.Base() + p.file.Size()),
		Imports:   p.imports,
		Comments:  p.comments,
	}
*/
/*
type File struct {
	Doc     *CommentGroup // associated documentation; or nil
	Package token.Pos     // position of "package" keyword
	Name    *Ident        // package name
	Decls   []Decl        // top-level declarations; or nil

	FileStart, FileEnd token.Pos       // start and end of entire file
	Scope              *Scope          // package scope (this file only)
	Imports            []*ImportSpec   // imports in this file
	Unresolved         []*Ident        // unresolved identifiers in this file
	Comments           []*CommentGroup // list of all comments in the source file
}
*/
class Identifier
{

};

struct Pos
{

};

struct Decl{};
struct Scope {};
struct ImportSpec {};
struct CommentGroup {};

class GoFile
{

public:
	CommentGroup* Doc;
	Pos Package;
	Identifier Name();
	std::vector<Decl> Decls;
	Pos FileStart, FileEnd;
	Scope* Scope;
	std::vector<ImportSpec> Imports;
	std::vector<Identifier> Unresolved;
	std::vector<CommentGroup> Comments;
};

