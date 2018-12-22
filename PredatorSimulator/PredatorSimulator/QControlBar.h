#ifndef Q_CONTROL_BAR_H
#define Q_CONTROL_BAR_H


#include <QWidget>

class QColorBox;
class QPushButton;
class QLabel;

class QControlBar : public QWidget
{
	Q_OBJECT

	static const QString sDefaultStartText, sDefaultStopText, sDefaultStepText, sDefaultPauseText, sDefaultResumeText, sAboutMessage;
	static const size_t sDefaultStateMarkerDepth;
	static const QColor sDefaultStateColor[4];
	static const QColor sDefaultBorderColor;

public:
	enum class State { NotReady = 0, Idle = 1, Active = 2, Pause = 3  };
	enum class Alignment { TowardFirst, TowardLast, Centered };

	QControlBar(Qt::Orientation orientation = Qt::Horizontal, Alignment alignment = Alignment::TowardLast, QWidget * parent = nullptr);

	void setText(QString const & startText, QString const & stopText, QString const & pauseText, QString const & resumeText, QString const & stepText);
	void setColor(QColor const & activeColor, QColor const & pauseColor, QColor const & idleColor, QColor const & notReadyColor, QColor const & borderColor = sDefaultBorderColor);

	State state() const { return mState; }

public slots:
	void setReady(bool isReady = true);
	void toggleStartStop();
	void togglePauseResume();
	void start();
	void stop();
	void pause();
	void resume();
	void step();
	void about();

signals:
	void started();
	void stopped();
	void paused();
	void resumed();
	void stepped();

protected:
	State mState;
	Qt::Orientation mOrientation;
	QString mStartText, mStopText, mStepText, mPauseText, mResumeText;
	QPushButton * mStartButton;
	QPushButton * mPauseButton;
	QPushButton * mStepButton;
	QPushButton * mAboutButton;
	QColorBox * mStateMarkerColorBox;

	QColor mStateColor[4];
	QColor mBorderColor;

	void updateGui();

};


#endif // Q_CONTROL_BAR_H