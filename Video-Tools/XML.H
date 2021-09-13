#ifndef I_XML
#define I_XML

#include <vector>

const int XMLERR_BADTAGNAME = -1;
const int XMLERR_TAGEXPECTED= -2;
const int XMLERR_OK         = 1;

struct XMLNODEATTRIBUTE
{
	char name[1024];
	char value[1024];
};

typedef std::vector< XMLNODEATTRIBUTE > XMLNODEATTRIBUTES;

class XMLNODE 
{
private:

public:
	XMLNODE();
	std::string	cNodeName;  // name of node
	std::string	cValue;     // value of node
	
	bool    bValuePresent;
	void*	pNext;      // next sibiling node on the same level
	void*   pChild;     // child node
	bool    bIsEmpty;
	XMLNODEATTRIBUTES	attributes;

    bool    ValuePresent() const
	{
		return bValuePresent;
	}
};

XMLNODE*	xmlAddChild(XMLNODE* pParent, char* cName, char* cValue, bool bIsEmpty = false);
void		xmlAddAttribute(XMLNODE* pNode, char* cName, char* cValue);
XMLNODE*	xmlAddSibling(XMLNODE** pNode, char* cName, char* cValue, bool bIsEmpty = false);
XMLNODE*	xmlAddSibling(XMLNODE* pNode, char* cName, char* cValue, bool bIsEmpty = false);

int			xmlTreeToString(XMLNODE* pNode, std::string& target);
void		xmlDeleteNode(XMLNODE** ppNode);
void		xmlDeleteSimpleNode(XMLNODE** ppNode);

int			xmlBuildTree(XMLNODE** pDest, char* cSourceText);
void		xmlRemoveNext(XMLNODE* pDest);

struct TOPO_SORT_ENTRY
{
	int		used;
	char*	cName1;
	char*   cName2;
};

struct TOPO_SORT_LIST
{
	int					iCount;
	TOPO_SORT_ENTRY**	entries;
} ;

int			xmlTopoSort(XMLNODE* pSource, XMLNODE** pDest, TOPO_SORT_LIST* pTSL);

#endif