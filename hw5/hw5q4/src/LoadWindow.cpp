#include "../lib/LoadWindow.h"
#include "Facile.h"
#include <QFile>
#include <QIODevice>
#include <QListWidgetItem>
#include <Qt>

LoadWindow::LoadWindow() {

	// LOAD WINDOW
	// overall layout
	loadLayout = new QVBoxLayout;
	
	// filename label & input
	// label
	filenameLabel = new QLabel("File Name:");
	loadLayout->addWidget(filenameLabel);

	// input
	filenameInput = new QLineEdit();
	QObject::connect(filenameInput, SIGNAL(returnPressed()), this, SLOT(loadFile()));
	loadLayout->addWidget(filenameInput);

	// load & quit button
	loadButton = new QPushButton("Load File");
	QObject::connect(loadButton, SIGNAL(clicked()),this, SLOT(loadFile()));
	loadLayout->addWidget(loadButton);

	quitButton_load = new QPushButton("Quit");
	QObject::connect(quitButton_load, SIGNAL(clicked()), this, SLOT(hideLoadWindow()));
	loadLayout->addWidget(quitButton_load);

	// Set overall layout
	setLayout(loadLayout);

	// Error window 
	errorLayout = new QVBoxLayout;
	otherWindow = new QWidget;
	
	errorLabel = new QLabel("Incorrect file name.");
	errorLayout->addWidget(errorLabel);
	
	// declare this in .h
	okButton = new QPushButton("OK");
	QObject::connect(okButton, SIGNAL(clicked()),this, SLOT(hideErrorWindow()));
	errorLayout->addWidget(okButton);

	otherWindow->setLayout(errorLayout);


	// DEBUGGER LAYOUT
	// Overall layout
	debuggerLayout = new QHBoxLayout;
	debuggerWindow = new QWidget;

	// Form to display line indicator
	lineWidget = new QWidget;
	lineArea = new QVBoxLayout;
	lineArea->addWidget(lineWidget);

	lineLsWidget = new QListWidget();
	QObject::connect(lineLsWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setLineNum(int)));
	lineArea->addWidget(lineLsWidget);

	lineLsWidget->setFixedWidth(40);

	// Form to display Facile text 
	// Layout
	textArea = new QVBoxLayout;
	statementWidget = new QListWidget();//QstatementWidget;
	QObject::connect(statementWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setLineNum(int)));
	textArea->addWidget(statementWidget);

	// Form to display 6 buttons to control Facile text
	// Layout
	controlArea = new QVBoxLayout;

	// buttons
	breakptButton = new QPushButton("Break Point");
	QObject::connect(breakptButton, SIGNAL(clicked()), this, SLOT(displayBreakpt()));
	controlArea->addWidget(breakptButton);

	continueButton = new QPushButton("Continue");
	QObject::connect(continueButton, SIGNAL(clicked()), this, SLOT(executeContinue()));
	controlArea->addWidget(continueButton);

	stepButton = new QPushButton("Step");
	QObject::connect(stepButton, SIGNAL(clicked()), this, SLOT(executeStep()));
	controlArea->addWidget(stepButton);

	nextButton = new QPushButton("Next");
	QObject::connect(nextButton, SIGNAL(clicked()), this, SLOT(executeNext()));
	controlArea->addWidget(nextButton);

	inspectButton = new QPushButton("Inspect");
	QObject::connect(inspectButton, SIGNAL(clicked()), this, SLOT(showValueWindow()));
	controlArea->addWidget(inspectButton);

	quitButton_dbugger = new QPushButton("Quit");
	QObject::connect(quitButton_dbugger, SIGNAL(clicked()), this, SLOT(hideDebugger()));
	controlArea->addWidget(quitButton_dbugger);
	
	// set all the layout to DEBUGGER WINDOW
	debuggerLayout->addLayout(lineArea);
	debuggerLayout->addLayout(textArea);
	debuggerLayout->addLayout(controlArea);

	debuggerWindow->setLayout(debuggerLayout);

	d_errorWindow = new QWidget;
	d_errorLayout = new QVBoxLayout;

	d_errorLabel = new QLabel;
	d_errorLayout->addWidget(d_errorLabel);

	d_okButton = new QPushButton ("OK");
	QObject::connect(d_okButton, SIGNAL(clicked()), this, SLOT(hideErrorWindow_d()));
	d_errorLayout->addWidget(d_okButton);

	d_errorWindow->setLayout(d_errorLayout);


	q_linenum = 0;
	m_curr = 0;
	q_highlight = 0;
	q_currBp = 0;


	// VALUE WINDOW
	valueLayout = new QHBoxLayout;
	valueWindow = new QWidget;

	// scroll box formLayout
	valueArea = new QVBoxLayout;
	valueLsWidget = new QListWidget;
	valueArea->addWidget(valueLsWidget);

	// radiobutton
	sortingArea = new QVBoxLayout;
	name_asc = new QRadioButton("Name ascending", this);
	QObject::connect(name_asc, SIGNAL(toggled(bool)), this, SLOT(sortingNameAsc()));
	sortingArea->addWidget(name_asc);

	name_desc = new QRadioButton("Name descending", this);
	QObject::connect(name_desc, SIGNAL(toggled(bool)), this, SLOT(sortingNameDesc()));
	sortingArea->addWidget(name_desc);

	num_asc = new QRadioButton("Value ascending", this);
	QObject::connect(num_asc, SIGNAL(toggled(bool)), this, SLOT(sortingValAsc()));
	sortingArea->addWidget(num_asc);

	num_desc = new QRadioButton("Value descending", this);
	QObject::connect(num_desc, SIGNAL(toggled(bool)), this, SLOT(sortingValDesc()));
	sortingArea->addWidget(num_desc);

	// hide & update button formLayout
	buttonArea = new QVBoxLayout;

	hideButton = new QPushButton("Hide") ;
	QObject::connect(hideButton, SIGNAL(clicked()), this, SLOT(hideValue()));
	buttonArea->addWidget(hideButton);

	updateButton = new QPushButton("Update");
	QObject::connect(updateButton, SIGNAL(clicked()), this, SLOT(updateValue()));
	buttonArea->addWidget(updateButton);

	// set all the layouts to VALUE WINDOW
	valueLayout->addLayout(valueArea);
	valueLayout->addLayout(sortingArea);
	valueLayout->addLayout(buttonArea);

	valueWindow->setLayout(valueLayout);

	q_sortValue = false;

}

LoadWindow::~LoadWindow() {

	// Deleting allocated memories for LOAD WINDOW
	delete filenameLabel;
	delete filenameInput;
	delete loadButton;
	delete quitButton_load;
	delete otherWindow;
	delete loadLayout;
	delete loadWindow; 

	delete errorLayout;
	delete okButton;
	delete errorLabel;

	// Deleting allocated memories for DEBUGGER WINDOW
	delete debuggerWindow;
	delete debuggerLayout;

	// facile text formlayout
	delete textArea;
	delete statementWidget;

	// code line indicator
	delete lineArea;
	delete lineWidget;
	delete lineLsWidget;

	// control formlayout
	delete controlArea;
	delete breakptButton;
	delete continueButton;
	delete stepButton;
	delete nextButton;
	delete inspectButton;
	delete quitButton_dbugger;

	// error window
	delete d_errorWindow;
	delete d_errorLayout;
	delete d_okButton;
	delete d_errorLabel;

	delete valueWindow;
	delete valueLayout;

	// scroll box formLayout
	delete valueArea;
	delete valueLsWidget;

	// radiobutton
	delete sortingArea;
	delete name_asc;
	delete name_desc;
	delete num_asc;
	delete num_desc;

	// hide & update button formLayout
	delete buttonArea;
	delete hideButton;
	delete updateButton;

	/*delete pstate;
	pstate->mapDeallocation();
	pstate = NULL;

	delete dbgr;
	dbgr = NULL;*/
}

void LoadWindow::loadFile() {

	filename = filenameInput->text();

	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly)) 
		setErrorWindow();
	else 	
		passToInterpreter();

}

void LoadWindow::passToInterpreter() {

	std::string f_name = filenameInput->text().toStdString();
	std::ifstream infile(f_name.c_str());
	Facile facile;
	
	pstate = new ProgramState(1);
	
	facile.interpretProgramHelper(infile, *this, program);
	pstate->setFacileLine(program.size());

	showDebugger();
}


void LoadWindow::hideLoadWindow() {

	this->hide();
}

void LoadWindow::setErrorWindow() {

	otherWindow->show();
}

void LoadWindow::hideErrorWindow() {

	otherWindow->hide();
}

void LoadWindow::showDebugger() {

	hideLoadWindow();
	debuggerWindow->show();	
}

void LoadWindow::hideDebugger() {

	debuggerWindow->hide();	
}

// storing statement and line number
void LoadWindow::storeStatement(std::string line, std::string line_num) {

	QString qstatement = QString::fromStdString(line);
	QString qlineNum = QString::fromStdString(line_num);

	dbgr = new Debugger;
	dbgr->setStatement(qstatement);
	dbgr->setLineNum(qlineNum);

	debugger.push_back(dbgr);

}

void LoadWindow::displayStatement() {

	for (unsigned int index=0; index < debugger.size(); index++) {

		statementWidget->addItem(debugger[index]->getStatement());
		lineLsWidget->addItem(debugger[index]->getLineNum());
	}
}

// BREAK POINT

void LoadWindow::displayBreakpt() {

	string breakpt = "[bp]  ";
	QListWidgetItem *item = statementWidget->item(q_bp);
	bool found = false;
	
	QString bp_line;

	// if there's no breakpoint 
	if (bpIndex.size() == 0) {

		QString itemText = item->text();
		bpStatement.push_back(itemText);
		item->setText(QString::fromStdString(breakpt) + itemText);
		statementWidget->insertItem(q_bp,item);
		bpIndex.push_back(q_bp);
	}
	else { // if breakpoint presents

		unsigned int i=0;

		for (i=0; i < bpIndex.size(); i++) {
		
			if (q_bp == bpIndex[i]) 
			{
				found = true;
				bpIndex.erase(bpIndex.begin() + i);
				bp_line = bpStatement[i];
				bpStatement.erase(bpStatement.begin() + i);
			}
		}

		if (!found) {

			QString itemText = item->text();
			bpStatement.push_back(itemText);
			item->setText(QString::fromStdString(breakpt) + itemText);
			statementWidget->insertItem(q_bp,item);
			bpIndex.push_back(q_bp);
		}
		else {
			item->setText(bp_line);
			statementWidget->insertItem(q_bp,item);
		
		}
		
	}

}

void LoadWindow::setLineNum(int row) {

	q_linenum = row + 1;
	q_bp = row;
	++q_highlight;
	lineLsWidget->item(row)->setSelected(true);
	lineLsWidget->setFocus();
}

// CONTINUE
void LoadWindow::executeContinue() {

	Facile facile;
	int mark = bpIndex.size()-1;

	q_linenum = bpIndex[mark] + 1; // start after bp
	--mark;

	while (q_linenum != bpIndex.front()) {

		exception();

		if (pstate->getEndProgram() == 1) {
			resetProgram();
		}
		if (pstate->getJump() == 1) {
			q_linenum = pstate->getQtLine();
			pstate->setJump(0);

			int temp = q_linenum + 1;
			q_linenum = pstate->getQtLine();

			if (pstate->getGosub() == 1) {
				stackint.push(temp++);
				pstate->setGosub(0);
			}
		}
		else { 

			if (pstate->getReturn() == 1) {
				q_linenum = stackint.top();
				stackint.pop();
				pstate->setReturn(0);
			}
			++q_linenum;
		}

		currLine(q_linenum);
		facile.QtInterpret(program, pstate, q_linenum);
	}

	int store = bpIndex.front();
	bpIndex.erase(bpIndex.begin());
	bpIndex.push_back(store);
}

// STEP
void LoadWindow::executeStep() {

	Facile facile;

	if (bpIndex.size() > 0) {

		exception();
			// when it hits END or .
		if (pstate->getEndProgram() == 1)
			resetProgram();

		// when it hit GOTO, GOSUB, or IF with jumpLine
		if (pstate->getJump() == 1) {
			pstate->setJump(0);
			
			int temp = q_linenum + 1;
			q_linenum = pstate->getQtLine();

			if (pstate->getGosub() == 1) {
				stackint.push(temp++);
				pstate->setGosub(0);
			}
		
		}
		else {// increment 1 step

			if (pstate->getReturn() == 1) {
				q_linenum = stackint.top();
				stackint.pop();
				pstate->setReturn(0);
			}
			else
				++q_linenum;
		}

		currLine(q_linenum);
		facile.QtInterpret(program, pstate, q_linenum);
	}
	else
		currLine(1);
}

// NEXT
void LoadWindow::executeNext() {

	Facile facile;

	if (bpIndex.size() > 0) {

		exception();
			// when it hits END or .
		if (pstate->getEndProgram() == 1)
			resetProgram();

		// when it hit GOTO, GOSUB, or IF with jumpLine
		if (pstate->getJump() == 1) 
		{
			pstate->setJump(0);
			
			// stack return index
			int temp = q_linenum + 1;
			q_linenum = pstate->getQtLine();

			currLine(q_linenum);
			facile.QtInterpret(program, pstate, q_linenum);

			if (pstate->getGosub() == 1) {
				stackint.push(temp++);
				pstate->setGosub(0);

				while (pstate->getReturn() != 1 || q_linenum != bpIndex.front()) {
					currLine(q_linenum);
					facile.QtInterpret(program, pstate, q_linenum);
					++q_linenum;
				}

				if (pstate->getReturn() == 1) {
					q_linenum = stackint.top();
					stackint.pop();
					pstate->setReturn(0);
					currLine(q_linenum);
					facile.QtInterpret(program, pstate, q_linenum);
				}

			}
		
		}
		else {// increment 1 step
			
			++q_linenum;
			currLine(q_linenum);
			facile.QtInterpret(program, pstate, q_linenum);
		}
		
	}
	else
		currLine(1);
	
}

void LoadWindow::resetProgram() {

	pstate = new ProgramState(1);
	pstate->setFacileLine(program.size());
	pstate->setEndProgram(0);
	q_linenum = 0;
}

// for storing statement after LoadButton
int LoadWindow::getLineNum() {

	return q_linenum;
}

void LoadWindow::currLine(int curr) {

	m_curr = curr;
	statementWidget->item(m_curr-1)->setSelected(true);
	statementWidget->setFocus();

	lineLsWidget->item(curr-1)->setSelected(true);
	lineLsWidget->setFocus();
}

void LoadWindow::exception() {

	if (pstate->divZero()) {
		showErrorWindow_d("Divided by 0 exception.");
		resetProgram();
	}
	
	if (pstate->outBound()) {
		showErrorWindow_d("Illegal jump instruction.");
		resetProgram();
	}

	if (pstate->getReturnError()) {
		showErrorWindow_d("Nothing to RETURN in the stack.");
		resetProgram();
	}
}

void LoadWindow::showErrorWindow_d(std::string errorMessage) {

	d_errorLabel->setText(QString::fromStdString(errorMessage));
	d_errorWindow->show();
}

void LoadWindow::hideErrorWindow_d() {

	d_errorWindow->hide();
}


// VALUE WINDOW
void LoadWindow::showValueWindow() {

	pstate->storeToValueWindow(mapValues, swap_mapValues);
	sortingNameAsc();
	displayMapValues();

	valueWindow->show();
}

void LoadWindow::displayMapValues() {

	if (!q_sortValue) {

		std::vector<std::pair<std::string, int> >::iterator it;
		Facile facile;
		// converting to QString then store it to QList
		for (it = mapValues.begin(); it != mapValues.end(); ++it) {

			QString qvar = QString::fromStdString(it->first);
			QString qval = QString::fromStdString(facile.intToString(it->second));
			q_mapValues.append(qMakePair(qvar, qval));
		}

		// displaying
		QList <QPair<QString,QString> >::iterator iter;

		for (iter = q_mapValues.begin(); iter != q_mapValues.end(); ++iter)
		{
			QString elem = iter->first + " " + iter->second;
			valueLsWidget->addItem(elem);
		}
	}
	else if (q_sortValue) {

		std::vector<std::pair<int, std::string> >::iterator it;
		Facile facile;
		// converting to QString then store it to QList
		for (it = swap_mapValues.begin(); it != swap_mapValues.end(); ++it) {

			QString qvar = QString::fromStdString(facile.intToString(it->first));
			QString qval = QString::fromStdString(it->second);
			q_mapValues.append(qMakePair(qvar, qval));
		}

		// displaying
		QList <QPair<QString,QString> >::iterator iter;

		for (iter = q_mapValues.begin(); iter != q_mapValues.end(); ++iter)
		{
			QString elem = iter->first + " " + iter->second;
			valueLsWidget->addItem(elem);
		}
	}
}

void LoadWindow::sortingNameAsc() {

	q_sortValue = false;
	comparatorAsc<std::pair<std::string, int> > comp;
	mergeSort(mapValues,comp);
}

void LoadWindow::sortingNameDesc() {

	q_sortValue = false;
	comparatorDesc<std::pair<std::string, int> > comp;
	mergeSort(mapValues,comp);
}

void LoadWindow::sortingValAsc() {

	q_sortValue = true;
	comparatorAsc<std::pair<int, std::string> > comp;
	mergeSort(swap_mapValues,comp);
}

void LoadWindow::sortingValDesc() {

	q_sortValue = true;
	comparatorDesc<std::pair<int, std::string> > comp;
	mergeSort(swap_mapValues,comp);	
}

void LoadWindow::updateValue() {

	valueLsWidget->clear();

	if(q_mapValues.size() > 0) 
		q_mapValues.clear();
		
	displayMapValues();
}

void LoadWindow::hideValue() {

	valueLsWidget->clear();
}