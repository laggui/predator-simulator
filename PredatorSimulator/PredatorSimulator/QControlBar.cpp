#include "QControlBar.h"

#include <QMessageBox>
#include <QLayout>
#include <QPushButton>
#include "QColorBox.h"

QString const QControlBar::sAboutMessage(
	"Objectif:\n"
	"PredatorSimulator est un jeu de simulation d'écosystème. "
	"Le but de cette simulation est de comprendre et d'utiliser "
	"le framework graphic view de Qt, et d'appliquer nos connaissances des paradigmes "
	"de l'orienté-objet en impliquant plusieurs classes qui interagissent entre elles.\n\n"
	"Explication de l'écosytème:\n"
	"Nous avons trois créatures différentes dans notre simulation, qui sont décrites ci-dessous.\n\n"
	"Les QRunner:\n"
	"Ces derniers essaient de traverser la zone de jeu en restant en vie. À la fin, une zone de clonage (en jaune) "
	"les téléporte au début de la scène où ils sont clonés pour augmenter la quantité de runners.\n\n"
	"Les QPredator:\n"
	"Ces joueurs ne se déplacent uniquement de gauche à droite en essayant d'attraper les runners. Chaque fois "
	"qu'un prédateur attrape un runner, ce dernier subit du dommage et perd de la vie. Lorsqu'un runner se fait toucher "
	"par un prédateur à son dernier point de vie (rouge), le prédateur le tue et il devient plus gros, ce qui le rend plus "
	"efficace pour attraper d'autre runners.\n\n"
	"Les QSuicideBomber:\n"
	"Aux grands maux les grands moyens! S'inspirant des kamikazes japonais de la 2e guerre mondiale, les runners ont réagit face "
	"à la menace des prédateurs. Les bombers sont des alliers des runners, qui peuvent uniquement en ligne droite. Si celui-ci "
	"se rend à la zone de clonage sans avoir attaqué un prédateur, il rebondit vers le haut au lieu de se cloner pour retourner "
	"attaquer les prédateurs. Lorsqu'un bomber réussi à entrer en contact avec un prédateur, il lui inflige du dommage qui le fait "
	"rétrécir, le rendant moins efficace à capturer des runners.\n\n"
	"Interaction avec l'écosystème:\n"
	"L'écosystème interagit avec toutes les entités dynamiques sur le terrain, soit les runners, les suicide bombers et les prédateurs. "
	"Après un certain temps prédéterminé, soit le temps d'évolution de l'écosystème, un nouveau runner ou suicide bomber (décision aléatoire) "
	"nait dans l'écosystème. Pour ce qui est des prédateurs, ils sont affaiblis si ça fait trop longtemps qu'ils n'ont pas tué un runner. Ainsi, "
	"les prédateurs rapetissent à cause du manque de nourriture après un temps prédéterminé. Comme vous pouvez aussi le remarquer, le terrain est "
	"délimité par des murs (rouge foncé) et une zone de clonage (jaune). La zone de clonage interagit avec les runners et les suicide bombers tel "
	"que mentionné précédemment, alors que les murs font rebondir toutes les entités dynamiques.\n\n\n"
	"Ce programme a été réalisé par : \n "
	"- Guillaume Lagrange\n"
	"- Jean-Simon Forest \n"
	"- Marc-André Maillé \n"
	"- Nicolas Champagne \n\n\n "
	"Dans le cadre du cours : \n "
	"- GPA777 - Introduction au génie logiciel \n"
	"- Laboratoire 3 \n"
	"Version 1.0 \n \n"
);
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
		mAboutButton{new QPushButton("À propos")},
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
	QMessageBox::about(this, "À propos de PredatorSimulator", sAboutMessage);
}

void QControlBar::updateGui()
{
	setEnabled(mState != State::NotReady);

	mStartButton->setText(mState == State::Active ? mStopText : mStartText);
	mStartButton->setEnabled(mState != State::Pause);

	mPauseButton->setText(mState == State::Pause ? mResumeText : mPauseText);
	mPauseButton->setEnabled(mState == State::Active || mState == State::Pause);

	mStepButton->setEnabled(mState == State::Pause);

	mStateMarkerColorBox->set(QBrush(mStateColor[static_cast<int>(mState)]));
	mStateMarkerColorBox->update();
}

