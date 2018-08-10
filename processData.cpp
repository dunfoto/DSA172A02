/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : Student code for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"


//------------------------------------------------------------------
class CommandIfo {
public:
	bool(*op)(char*, L1List<VRecord>&);
	char *cmd;
	CommandIfo(char *c, bool(*inop)(char*, L1List<VRecord>&)) {
		cmd = c;
		op = inop;
	}

	CommandIfo(char *c) {
		op = NULL;
		cmd = c;
	}

	void print() {
		cout << cmd << endl;
	}

	CommandIfo() : cmd(NULL), op(NULL) {}

	bool run(char *args, L1List<VRecord>& recList) {
		return op(args, recList);
	}

	bool operator==(CommandIfo c) {
		bool ret = isTrue(c.cmd);
		return ret;
	}

	bool isTrue(char *c) {
		return strcmp(cmd, c) == 0;
	}
};

class CommandManager {
private:
	CommandIfo AtrNULL;
	L1List<CommandIfo> mCommand;

	bool getCommand(VRequest& request, CommandIfo& info) {
		char *cmd = request.getCmd();
		int idx = -1;
		CommandIfo tmp(cmd);
		if (mCommand.find(tmp, idx)) {
			info = mCommand[idx];
			return true;
		}
		return false;
	}

	char* getArgs(VRequest& request) {
		char *arg = request.getArgs();
		if (strlen(arg) == 0) {
			return NULL;
		}
		return arg;
	}
public:
	CommandManager() {};
	~CommandManager() {};

	int getSize(){
		return mCommand.getSize();
	}

	void registerCommand(char *cmd, bool(*inop)(char*, L1List<VRecord>&)) {
		CommandIfo command = CommandIfo(cmd, inop);
		mCommand.push_back(command);
	}

	bool process(VRequest& request, L1List<VRecord>& recList) {
		CommandIfo p;
		bool ret = getCommand(request, p);
		if (!ret) return false;
		char *args = getArgs(request);
		return p.run(args, recList);
	}
};

/**
* =============================================================================
*
* IMPLEMENT ALL FEATURE
*
* =============================================================================
* */
void devices(VRecord &data, void *list){
	L1List<VRecord>* l = (L1List<VRecord>*) list;
	if (!l->exist(data)) l->insertHead(data);
}

void devices_resetX(VRecord &data, void *list){
	L1List<VRecord>* l = (L1List<VRecord>*) list;
	int idx = -1;
	if (!l->find(data, idx)){
		l->insertHead(data);
		l->at(0).x = 1.0;
	}
	else {
		l->at(idx).x += 1.0;
	}
}

void findDevice(VRecord &data, void *cmp) {
	VRecord *r = (VRecord *)cmp;
	if (*r == data) {
		r->x = data.x;
		r->y = data.y;
		r->timestamp = data.timestamp;
	}
}

void getRoD(VRecord &data, void *list) {
	L1List<VRecord>* l = (L1List<VRecord>*) list;
	if (data == l->at(0)) {
		l->push_back(data);
	}
}

bool checkLocation(VRecord& a, VRecord& b) {
	return distanceVR(a.y, a.x, b.y, b.x) < 0.005;
}

void getStopRecords(VRecord &data, void *list) {
	L1List<VRecord> *ls = (L1List<VRecord>*) list;
	if (ls->isEmpty()) ls->insertHead(data);
	else {
		if (ls->getSize() == 1) {
			if (checkLocation(ls[0][0], data)){
				ls->insertHead(data);
			}
			else {
				ls->removeHead();
				ls->insertHead(data);
			}
		}
		else {
			if (checkLocation(ls[0][0], data)) {
				ls->insertHead(data);
			}
			else {
				if (checkLocation(ls[0][0], ls[0][1])) {
					ls->insertHead(data);
				}
				else {
					ls->removeHead();
					ls->insertHead(data);
				}
			}
		}
	}
}

void removeStopRecords(L1List<VRecord> *ls) {
	if (ls->isEmpty() || ls->getSize() == 1) {
		ls->clean();
		return;
	}
	if (!checkLocation(ls[0][0], ls[0][1])) {
		ls->removeHead();
	}
}

void getMax(VRecord &data, void *list){
	L1List<VRecord> *l = (L1List<VRecord>*) list;
	if (data.x >= l->at(0).x){
		l->removeHead();
		l->insertHead(data);
	}
}

void getMin(VRecord &data, void *list){
	L1List<VRecord> *l = (L1List<VRecord>*) list;
	if (data.x <= l->at(0).x){
		l->removeHead();
		l->insertHead(data);
	}
}


//------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------




/// Initialize and Finalize any global data that you use in the program

bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here

    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.
    return true;
}

