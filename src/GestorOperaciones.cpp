#include "GestorOperaciones.h"
#include <iostream>

QString GestorOperaciones::generarOperacionMatematica(const Proceso& proceso)
{
        int num1 = proceso.numero1;
        int num2 = proceso.numero2;
	Operacion op = static_cast<Operacion>(proceso.indiceOperacion);
	switch (op) {
		case SUMA: return QString("%1 + %2").arg(num1).arg(num2);
		case RESTA: return QString("%1 - %2").arg(num1).arg(num2);
		case MULTIPLICACION: return QString("%1 * %2").arg(num1).arg(num2);
		case DIVISION: return QString("%1 / %2").arg(num1).arg(num2);
		case MODULO: return QString("%1 % %2").arg(num1).arg(num2);
		case POTENCIA: return QString("%1 ^ %2").arg(num1).arg(num2);
		default: return QString("%1 + %2").arg(num1).arg(num2);
	}
}

QString GestorOperaciones::calcularResultado(const Proceso& proceso)
{
        if (proceso.tiempoTranscurrido < proceso.tiempoEstimado) return "Error";
        int num1 = proceso.numero1;
        int num2 = proceso.numero2;
        Operacion op = static_cast<Operacion>(proceso.indiceOperacion);
        switch (op) {
                case SUMA: return QString::number(num1 + num2);
                case RESTA: return QString::number(num1 - num2);
                case MULTIPLICACION: return QString::number(num1 * num2);
                case DIVISION: return QString::number(num2 != 0 ? static_cast<float>(num1) / num2 : 0.0);
                case MODULO: return QString::number(num2 != 0 ? num1 % num2 : 0);
                case POTENCIA: return QString::number(pow(num1, num2));
                default: return QString("Error");
        }
        return "Error";
}
