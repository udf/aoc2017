#include <Array.au3>
#include <StringConstants.au3>

; load data
$aBanks = StringRegExp(FileRead("input.txt"), "(\d+)", $STR_REGEXPARRAYGLOBALMATCH)
$iBanklen = UBound($aBanks)
For $i = 0 To $iBanklen - 1
	$aBanks[$i] = Int($aBanks[$i])
Next

$iIterCount = 0
$oDictionary = ObjCreate("Scripting.Dictionary")
While True
	$iIterCount += 1

	; find largest and clear it
	$iMaxInd = _ArrayMaxIndex($aBanks, 1)
	$iBlockCount = $aBanks[$iMaxInd]
	$aBanks[$iMaxInd] = 0

	; distribute banks
	For $i = $iMaxInd + 1 To $iMaxInd + $iBlockCount
		$aBanks[Mod($i, $iBanklen)] += 1
	Next

	; exitloop if we have seen it before
	$sBanks = _ArrayToString($aBanks, " ")
	If $oDictionary.Exists($sBanks) Then
		ExitLoop
	EndIf
	$oDictionary.Add($sBanks, "")
WEnd

ConsoleWrite($iIterCount & @CRLF)