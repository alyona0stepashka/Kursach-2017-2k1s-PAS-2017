#include "stdafx.h"
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] = //òàáëèöà îøèáîê
	{
		ERROR_ENTRY(0, "[SYSTEM]: Íåäîïóñòèìûé êîä îøèáêè"), 
		ERROR_ENTRY(1, "[SYSTEM]: Ñèñòåìíûé ñáîé"),
		ERROR_ENTRY(2, "[SYSTEM]: Íåäîïóñòèìîå êîëè÷åñòâî îøèáîê"),
		ERROR_ENTRY(3, "[SYSTEM]: "),
		ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		
		ERROR_ENTRY(100, "[PARM]: Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "[PARM]: Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà"),//+
		ERROR_ENTRY_NODEF(105),	ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		
		ERROR_ENTRY(110, "[IN]: Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
		ERROR_ENTRY(111, "[IN]: Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
		ERROR_ENTRY(112, "[IN]: Ïğåâûøåí ïğåäåë ğàçìåğà âõîäíîãî êîäà"),
		ERROR_ENTRY(113, "[IN]: Ïğåâûøåí ïğåäåë ğàçìåğà òîêåíà"),
		ERROR_ENTRY(114, "[IN]: Îòñóòñòâóåò çàêğûâàşùàÿ êàâû÷êà"),
		ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116),	ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120, "[LexA]: Îøèáêà ïğè ğàçáîğå òîêåíà"),
		ERROR_ENTRY(121, "[LexA]: Èñïîëüçóåòñÿ íåîáúÿâëåííûé èäåíòèôèêàòîğ"),
		ERROR_ENTRY(122, "[LexA]: Ïåğåïîëíåíèå òàáëèöû èäåíòèôèêàòîğîâ"),
		ERROR_ENTRY(123, "[LexA]: Ïåğåïîëíåíèå òàáëèöû ëåêñåì"),
		ERROR_ENTRY(124, "[LexA]: Îòñóòñòâóåò òî÷êà âõîäà"),
		ERROR_ENTRY(125, "[LexA]: Îáíàğóæåíî íåñêîëüêî òî÷åê âõîäà"),
		ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127),
		ERROR_ENTRY_NODEF(128),	ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600, "[SinA]: Íåâåğíàÿ ñòğóêòóğà ïğîãğàììû"),
		ERROR_ENTRY(601, "[SinA]: Îøèáî÷íûé îïåğàòîğ"),
		ERROR_ENTRY(602, "[SinA]: Îøèáêà â âûğàæåíèè"),
		ERROR_ENTRY(603, "[SinA]: Îøèáêà â ïàğàìåòğàõ ôóíêöèè"),
		ERROR_ENTRY(604, "[SinA]: Îøèáêà â ïàğàìåòğàõ âûçûâàåìîé ôóíêöèè"),
		ERROR_ENTRY(605, "[SinA]: Îøèáêà çíàêà â âûğàæåíèè"),
		ERROR_ENTRY(606, "[SinA]: Îøèáêà â ñèíòàêñè÷åñêîì àíàëèçå"),
		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY(609, "[SinA]: Îáíàğóæåíà ñèíòàêñè÷åñêàÿ îøèáêà (æóğíàë Log)"),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),


		ERROR_ENTRY(700, "[SemA]: Ïîâòîğíîå îáúÿâëåíèå èäåíòèôèêàòîğà"),
		ERROR_ENTRY(701, "[SemA]: Îøèáêà â âîçâğàùàåìîì çíà÷åíèè"),
		ERROR_ENTRY(702, "[SemA]: Îøèáêà â ïåğåäàâàåìûõ çíà÷åíèÿõ â ôóíêöèè"),
		ERROR_ENTRY(703, "[SemA]: Â ôóíêöèş íå ïåğåäàíû ïàğàìåòğû"),
		ERROR_ENTRY(704, "[SemA]: Òèï äàííûõ ğåçóëüòàòà âûğàæåíèÿ íå ñîîòâåòñòâóåò èäåíòèôèêàòîğó"),
		ERROR_ENTRY_NODEF(705),	ERROR_ENTRY_NODEF(706),
		ERROR_ENTRY_NODEF(707),	ERROR_ENTRY_NODEF(708),	ERROR_ENTRY_NODEF(709),
		ERROR_ENTRY_NODEF10(710),ERROR_ENTRY_NODEF10(720),ERROR_ENTRY_NODEF10(730),ERROR_ENTRY_NODEF10(740),
		ERROR_ENTRY_NODEF10(750),ERROR_ENTRY_NODEF10(760),ERROR_ENTRY_NODEF10(770),ERROR_ENTRY_NODEF10(780),
		ERROR_ENTRY_NODEF10(790),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if ((id > 0) && (id < ERROR_MAX_ENTRY))
		{
			return errors[id];
		}
		else
		{
			return errors[0];
		}
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if ((id > 0) && (id < ERROR_MAX_ENTRY))
		{
			errors[id].inext.line = line;
			errors[id].inext.col = col;
			return errors[id];
		}
		else
		{
			errors[0].inext.line = line;
			errors[0].inext.col = col;
			return errors[0];
		}
	}
	void ARR_OF_ERRORS::AddErr(int id, int line, int col)
	{
		errors[size] = ERROR_THROW_IN(id, line, col);
		size++;
		CheckSize();
	}
	void ARR_OF_ERRORS::CheckSize()
	{
		if (size == 10)
			throw *this;
	}
}