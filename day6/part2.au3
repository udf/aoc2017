#include <Array.au3>
#include <StringConstants.au3>

Func _DoRedistribute(ByRef $aBanks, $iBanklen)
	; find largest and clear it
	$iMaxInd = _ArrayMaxIndex($aBanks, 1)
	$iBlockCount = $aBanks[$iMaxInd]
	$aBanks[$iMaxInd] = 0

	; distribute banks
	For $i = $iMaxInd + 1 To $iMaxInd + $iBlockCount
		$aBanks[Mod($i, $iBanklen)] += 1
	Next

	Return _ArrayToString($aBanks, " ")
EndFunc

; load data
$aBanks = StringRegExp(FileRead("input.txt"), "(\d+)", $STR_REGEXPARRAYGLOBALMATCH)
$iBanklen = UBound($aBanks)
For $i = 0 To $iBanklen - 1
	$aBanks[$i] = Int($aBanks[$i])
Next

$oDictionary = ObjCreate("Scripting.Dictionary")
$sLoopStart = ""
While True
	$sBanks = _DoRedistribute($aBanks, $iBanklen)
	; store it and exitloop if we have seen it before
	If $oDictionary.Exists($sBanks) Then
		$sLoopStart = $sBanks
		ExitLoop
	EndIf
	$oDictionary.Add($sBanks, "")
WEnd

$iIterCount = 0
Do
	$iIterCount += 1
Until _DoRedistribute($aBanks, $iBanklen) == $sLoopStart

ConsoleWrite($iIterCount & @CRLF)