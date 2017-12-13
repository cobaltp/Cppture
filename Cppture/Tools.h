#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <tchar.h>

namespace Tools
{
	bool GetProductAndVersion(QString &strProductName, QString &strProductVersion);

	namespace KeySequence
	{
		Qt::Key getKey(const QKeySequence &keySequence);
		Qt::KeyboardModifiers getModifiers(const QKeySequence &keySequence);
		quint32 toNativeVirtualKey(Qt::Key key);
		quint32 toNativeModifiers(Qt::KeyboardModifiers modifiers);
		quint32 getNativeVirtualKey(const QKeySequence &keySequence);
		quint32 getNativeModifiers(const QKeySequence &keySequence);
	}
}