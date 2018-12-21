#include "QControlBar.h"

#include <QMessageBox>
#include <QLayout>
#include <QPushButton>
#include "QColorBox.h"


QString const QControlBar::sDefaultStartText("Start");
QString const QControlBar::sDefaultStopText("Stop");
QString const QControlBar::sDefaultStepText("Step");
QString const QControlBar::sDefaultPauseText("Pause");
QString const QControlBar::sDefaultResumeText("Resume");

const size_t QControlBar::sDefaultStateMarkerDepth{ 3 };
const QColor QControlBar::sDefaultStateColor[4]{ 
							QColor(220, 220, 220),				// to do : must be from QPalette
							QColor(196, 0, 0), 
							QColor(0, 196, 0),
							QColor(222, 210, 0) 
						};
const QColor QControlBar::sDefaultBorderColor(128, 128, 128);	// to do : must be from QPalette

QControlBar::QControlBar(Qt::Orientation orientation, Alignment alignment, QWidget * parent)
	:	QWidget(parent),
		mOrientation{ orientation },
		mState{ State::NotReady },
		mStartText(sDefaultStartText),
		mStopText(sDefaultStopText),
		mStepText(sDefaultStepText),
		mPauseText(sDefaultPauseText),
		mResumeText(sDefaultResumeText),
		mStartButton{ new QPushButton(mStartText) },
		mPauseButton{ new QPushButton(mPauseText) },
		mStepButton{ new QPushButton(mStepText) },
		mAboutButton{new QPushButton("à propos")},
		mStateMarkerColorBox{ new QColorBox },
		mStateColor{ sDefaultStateColor[0], sDefaultStateColor[1], sDefaultStateColor[2], sDefaultStateColor[3] },
		mBorderColor(sDefaultBorderColor)
{
	QLayout * layout;
	if (orientation == Qt::Horizontal) {
		layout = new QHBoxLayout;
		mStateMarkerColorBox->setFixedWidth(sDefaultStateMarkerDepth);
		if (alignment != Alignment::TowardFirst) {
			static_cast<QHBoxLayout*>(layout)->addStretch();
		}
		layout->addWidget(mStartButton);
		layout->addWidget(mPauseButton);
		layout->addWidget(mStepButton);
		layout->addWidget(mAboutButton);
		if (alignment != Alignment::TowardLast) {
			static_cast<QHBoxLayout*>(layout)->addStretch();
		}
	} else {
		layout = new QVBoxLayout;
		mStateMarkerColorBox->setFixedHeight(sDefaultStateMarkerDepth);
		if (alignment != Alignment::TowardFirst) {
			static_cast<QVBoxLayout*>(layout)->addStretch();
		}
		layout->addWidget(mStartButton);
		
		layout->addWidget(mPauseButton);
		layout->addWidget(mStepButton);
		layout->addWidget(mStateMarkerColorBox);
		layout->addWidget(mAboutButton);
		if (alignment != Alignment::TowardLast) {
			static_cast<QVBoxLayout*>(layout)->addStretch();
		}
	}

	setLayout(layout);

	connect(mStartButton, &QPushButton::clicked, this, &QControlBar::toggleStartStop);
	connect(mPauseButton, &QPushButton::clicked, this, &QControlBar::togglePauseResume);
	connect(mStepButton, &QPushButton::clicked, this, &QControlBar::step);
	connect(mAboutButton, &QPushButton::clicked, this, &QControlBar::about);

	updateGui();
}

void QControlBar::setText(QString const & startText, QString const & stopText, QString const & pauseText, QString const & resumeText, QString const & stepText)
{
	mStartText = startText;
	mStopText = stopText;
	mPauseText = pauseText;
	mResumeText = resumeText;
	mStepText = stepText;

	mStepButton->setText(mStepText);
	updateGui();
}

void QControlBar::setColor(QColor const & activeColor, QColor const & pauseColor, QColor const & idleColor, QColor const & notReadyColor, QColor const & borderColor)
{
	mStateColor[0] = notReadyColor;
	mStateColor[1] = idleColor;
	mStateColor[2] = activeColor;
	mStateColor[3] = pauseColor;
	mBorderColor = borderColor;

	mStateMarkerColorBox->set(QPen(mBorderColor));
}

void QControlBar::setReady(bool isReady)
{
	if (isReady && mState == State::NotReady) {
		mState = State::Idle;
	}
	if (!isReady) {
		if (mState == State::Active) {
			stop();
		}
		mState = State::NotReady;
	}
	updateGui();
}

void QControlBar::toggleStartStop()
{
	switch (mState) {
		case QControlBar::State::Idle:
			start();
			break;
		case QControlBar::State::Active:
			stop();
			break;
	}
}

void QControlBar::togglePauseResume()
{
	switch (mState) {
		case QControlBar::State::Active:
			pause();
			break;
		case QControlBar::State::Pause:
			resume();
			break;
	}
}

void QControlBar::start()
{
	if (mState == State::Idle) {
		mState = State::Active;
		emit started();
		updateGui();
	}
}

void QControlBar::stop()
{
	if (mState == State::Active) {
		mState = State::Idle;
		emit stopped();
		updateGui();
	}
}

void QControlBar::pause()
{
	if (mState == State::Active) {
		mState = State::Pause;
		emit paused();
		updateGui();
	}
}

void QControlBar::resume()
{
	if (mState == State::Pause) {
		mState = State::Active;
		emit resumed();
		updateGui();
	}
}

void QControlBar::step()
{
	if (mState == State::Idle || mState == State::Pause) {
		emit stepped();
	}
}

void QControlBar::about()
{
	QMessageBox::about(this,
		"À propos de CppXtract",
		"CppXtract est un logiciel d'extraction de commentaires du langage C++ \n \n "
		"Ce programme a été réalisé par : \n "
		"-Jean-Simon Forest \n"
		"- Nicolas Champagne \n \n \n "
		"Dans le cadre du cours : \n "
		"-GPA 777 - Introduction au génie logicial \n"
		"-Laboratoire 2 \n \n"
		"Version 1.0 \n \n"
		"-------------------------------\n"
		"Présentation sommaite de l'extension \n"
		"--------------------------------\n"
		"Description de l'estentiorenfsdasad;uaobfsahiòfvounoîfa");
}

void QControlBar::updateGui()
{
	setEnabled(mState != State::NotReady);

	mStartButton->setText(mState == State::Active ? mStopText : mStartText);
	mStartButton->setEnabled(mState != State::Pause);

	mPauseButton->setText(mState == State::Pause ? mResumeText : mPauseText);
	mPauseButton->setEnabled(mState == State::Active || mState == State::Pause);

	mStepButton->setEnabled(mState != State::Active);

	mStateMarkerColorBox->set(QBrush(mStateColor[static_cast<int>(mState)]));
	mStateMarkerColorBox->update();
}

