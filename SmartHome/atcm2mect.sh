#!/bin/bash

for f in *.h *.cpp *.ui; do
	echo -ne "$f:\t"

	echo -ne " 1"; sed -i 's/atcmplugin\.h/mectplugin.h/g'                           $f || exit 1

	echo -ne " 2"; sed -i 's/atcmbutton\.h/mectbutton.h/g'                           $f || exit 1
	echo -ne " 3"; sed -i 's/ATCMlabel::Dec/MECTlabel::MECTLabelFormat::Dec/g'       $f || exit 1
	echo -ne " 4"; sed -i 's/ATCMlabel::Hex/MECTlabel::MECTLabelFormat::Hex/g'       $f || exit 1
	echo -ne " 5"; sed -i 's/ATCMlabel::Bin/MECTlabel::MECTLabelFormat::Bin/g'       $f || exit 1
	echo -ne " 6"; sed -i 's/ATCMlabel/MECTlabel/g'                                  $f || exit 1
	echo -ne " 7"; sed -i '/<property name="refresh">/,/<\/property>/d'              $f || exit 1

	echo -ne " 8"; sed -i 's/atcmdate\.h/mectdate.h/g'                               $f || exit 1
	echo -ne " 9"; sed -i 's/ATCMdate/MECTdate/g'                                    $f || exit 1

	echo -ne " a"; sed -i 's/atcmtime\.h/mecttime.h/g'                               $f || exit 1
	echo -ne " b"; sed -i 's/ATCMtime/MECTtime/g'                                    $f || exit 1

	echo -ne " c"; sed -i 's/atcmbutton\.h/mectbutton.h/g'                           $f || exit 1
	echo -ne " d"; sed -i 's/ATCMbutton/MECTbutton/g'                                $f || exit 1
	echo -ne " e"; sed -i 's/property name="statusvar"/property name="variable"/g'   $f || exit 1
	echo -ne " f"; sed -i 's/newPage(const char\*,bool)/newPage(QString,bool)/g'     $f || exit 1
	echo -ne " g"; sed -i 's/goto_page(const char\*,bool)/goto_page(QString,bool)/g' $f || exit 1

	echo -ne " h"; sed -i 's/atcmled\.h/mectled.h/g'                                 $f || exit 1
	echo -ne " i"; sed -i 's/ATCMled/MECTled/g'                                      $f || exit 1

	echo -ne " j"; sed -i 's/atcmcombobox\.h/mectcombobox.h/g'                       $f || exit 1
	echo -ne " k"; sed -i 's/ATCMcombobox/MECTcombobox/g'                            $f || exit 1

	echo -ne " ok\n"
done	
