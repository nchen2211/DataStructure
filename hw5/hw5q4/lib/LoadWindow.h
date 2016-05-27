#ifndef LOADWINDOW_H
#define LOADWINDOW_H
#include "Statement.h"
#include "msort.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QDebug>
#include <QRadioButton>
#include <QList>
#include <QPair>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 

class LoadWindow;

struct Debugger {

public:

	void setStatement (QString str) {facileStatement = str;};
	void setLineNum (QString st) {lineNum = st;};
	void setBreakpt (QString x) {breakpt = x;};

	QString getStatement() {return facileStatement;};
	QString getLineNum() {return lineNum;};
	QString getBreakpt() {return breakpt;};

private:

	QString facileStatement;
	QString lineNum;
	QString breakpt;
};

class LoadWindow : public QWidget {

	Q_OBJECT

public:
	LoadWindow();
	~LoadWindow();

public slots:
	
	// LOAD WINDOW FUNCTION
	// add, load filename related
	void loadFile();
	void passToInterpreter();
	void hideLoadWindow();

	// other window
	void setErrorWindow();
	void hideErrorWindow(); //Possibly be a pure virtual in base class
	
	// DEBUGGER WINDOW FUNCTIONS
	// setting up debugger window
	void storeStatement(std::string line, std::string line_num);
	void displayStatement();
	void showDebugger();
	void hideDebugger();

	void executeStep();
	void executeContinue();
	void executeNext();

	void resetProgram();
	//void stackReturn();

	void exception();
	void showErrorWindow_d(std::string);
	void hideErrorWindow_d();

	// breakpt, step, next, continue
	void currLine(int);
	void setLineNum(int);
	int getLineNum();
	void displayBreakpt();

	// VALUE WINDOW
	void showValueWindow();
	void displayMapValues();

	//sorting
	void sortingNameAsc();
	void sortingNameDesc();
	void sortingValAsc();
	void sortingValDesc();
	void hideValue();
	void updateValue();



private:
	//LOAD WINDOW
	//layouts
	QVBoxLayout *loadLayout;
	QWidget *loadWindow; 
	QWidget *otherWindow;

	//Entering a filename
	QLabel *filenameLabel;
	QLineEdit *filenameInput;
	QString filename;

	//Buttons
	QPushButton *loadButton;
	QPushButton *quitButton_load;

	//Error Label
	QVBoxLayout *errorLayout;
	QPushButton *okButton;
	QLabel *errorLabel;


	// DEBUGGER WINDOW
	// main layout
	QWidget *debuggerWindow;
	QHBoxLayout *debuggerLayout;

	// facile text formlayout
	QVBoxLayout *textArea;
	QListWidget *statementWidget;

	// code line indicator
	QVBoxLayout *lineArea;
	QWidget *lineWidget;
	QListWidget *lineLsWidget;

	// control formlayout
	QVBoxLayout *controlArea;
	QPushButton *breakptButton;
	QPushButton *continueButton;
	QPushButton *stepButton;
	QPushButton *nextButton;
	QPushButton *inspectButton;
	QPushButton *quitButton_dbugger;

	// error window
	QWidget *d_errorWindow;
	QVBoxLayout *d_errorLayout;
	QPushButton *d_okButton;
	QLabel *d_errorLabel;


	// VALUE WINDOW
	// main layout
	QWidget *valueWindow;
	QHBoxLayout *valueLayout;

	// scroll box formLayout
	QVBoxLayout *valueArea;
	QListWidget *valueLsWidget;

	// radiobutton
	QVBoxLayout *sortingArea;
	QRadioButton *name_asc;
	QRadioButton *name_desc;
	QRadioButton *num_asc;
	QRadioButton *num_desc;

	// hide & update button formLayout
	QVBoxLayout *buttonArea;
	QPushButton *hideButton;
	QPushButton *updateButton;

	std::vector<Statement*> program;
	ProgramState *pstate;
	//Debugger component: facile statement, code line, and breakpoint indicator
	std::vector<Debugger*> debugger;
	std::vector<int> bpIndex;
	std::vector<QString> bpStatement;

	Debugger *dbgr;
	int q_highlight;
	int q_linenum;
	int q_bp;
	int m_curr;
	int q_currBp;
	bool q_sortValue;

	int q_return;

	// Value window
	std::vector<std::pair<std::string,int> > mapValues;
	std::vector<std::pair<int, std::string> > swap_mapValues;
	QList <QPair<QString, QString> > q_mapValues;
	StackInt stackint;
};

#endif