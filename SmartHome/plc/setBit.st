(****************************************************************************
**
** Copyright (C) 2021 Francesco Mandracci
** Contact: https://github.com/fmandracci/smart-home
**
** This file is part of the Smart Home Framework.
**
** Commercial License Usage
** Licensees holding valid commercial licenses may use this file in
** accordance with the terms contained in a written agreement
** between you and the copyright owner.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
****************************************************************************)

FUNCTION setBit
VAR_INPUT
    mask : WORD;
    value : BOOL;
END_VAR
VAR_IN_OUT
    u : UINT;
END_VAR
VAR
	w : WORD;
END_VAR

	w := UINT_TO_WORD(u);
	if value then
		w := w or mask;
	else
		w := w and not mask;
	end_if;
	u := WORD_TO_UINT(w);

END_FUNCTION
