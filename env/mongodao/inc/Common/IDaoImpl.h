#ifndef INC_COMMON_IDAOIMPL_H_
#define INC_COMMON_IDAOIMPL_H_

#include <list>
#include "Document.h"

namespace DB {
namespace Common {

class IDaoImpl
{
public:
	virtual ~IDaoImpl();

	virtual void Create(const Document& doc_) = 0;
	//virtual void Read() = 0;
	virtual std::list<Document> ReadAll() = 0;
	virtual void Update(const Document& doc_, const std::string &column_, const std::string &old_, const std::string &new_) = 0;
	virtual void Delete(const Document& doc_) = 0;
	virtual void DeleteAll(const std::list<Document&> doc_);

private:

};

}}

#endif // INC_COMMON_IDAOIMPL_H_
