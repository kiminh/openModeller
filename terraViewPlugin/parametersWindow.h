#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <parametersForm.h>

#include <qvbox.h>
#include <qwidget.h>
#include <qscrollview.h>
#include <qlayout.h>
#include <qsettings.h> 
#include <qlabel.h> 
#include <qpushbutton.h> 
#include <om.hh>
class parametersWindow : public parametersForm
{
Q_OBJECT

public:
	/**
	* Default constructor.
	*/
	parametersWindow( QStringList* algorithmParameters );

	~parametersWindow();

    /**
	* Get algorithm parameter list (from omgui).
	*/
	void getParameterList( QString theAlgorithmNameQString );

	/**
	* Read paramteres from register.
	*/
	void readParametes( const QString algID );
	/**
	* Write paramteres in register.
	*/
	void writeParametes();

	void ok() { accept(); }

	/**
	* Qt functions.
	*/
	// (from omgui)
	void defaulsParametersPushButton_clicked();
	void okPushButton_clicked();

private:
	OpenModeller* mOpenModeller;

	QScrollView* mParametersScrollView;
    QVBox* mParametersVBox;
	QScrollView* mScrollView;

	QStringList* extraParametersQStringList;
};

#endif