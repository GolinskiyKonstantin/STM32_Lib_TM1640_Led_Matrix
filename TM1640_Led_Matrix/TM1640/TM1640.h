/*


	ВНИМАНИЕ !!!  в этот файл записываем только обЪявления структур, перечислений,
	прототипы функций, define и т.д.
	
	ВНИМАНИЕ !!! в этот файл записывать нельзя объявление переменных, обЪявления функций,
	инициализация структур и переменных, выделять память и т.д это все делаем в файле.с
	
	
	
  ******************************************************************************
  * @file 			( фаил ):   TM1640.h
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):
  ******************************************************************************
  
*/

#ifndef _TM1640_H
#define _TM1640_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------*/

// Обязательно нужен #include "main.h" 
// чтоб отдельно не подключать файлы связанные с МК и стандартными библиотеками
#include "main.h"

#include "string.h"
#include <stdlib.h>		// для функции malloc()

//***********   настройки портов DIN CLK ***************************************************************

// управление по двум портам ( настроины как выход без подтяжки )
// для работы всеголиш меняем на портах логические уровни
// используем библиотеку HAL, если не через HAL то перепределяем
#define DIN(x)		HAL_GPIO_WritePin( GPIOB, GPIO_PIN_7, x ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define read_DIN	HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_7 )
#define CLK(x)		HAL_GPIO_WritePin( GPIOB, GPIO_PIN_6, x ? GPIO_PIN_SET : GPIO_PIN_RESET)

//*******************************************************************************************************

#define DELAY_TIME 				100			// кол-во микросекунл задержек в функциях	
#define BRIGHTNESS_TM1640		1			// контрастность дисплея по умолчанию ( всего от 0 до 7 )

#define HIGH					1			// GPIO_PIN_SET
#define LOW						0			// GPIO_PIN_RESET
	
/* Functions prototypes ----------------------------------------------*/

/*
	******************************************************************************
	* @brief	 ( описание ):  функция задержки в микросекундах
	* @param	( параметры ):	кол-во микросекунд
	* @return  ( возвращает ):	

	******************************************************************************
*/
void Delay_us( uint32_t i );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция для старта ( активации ) передачи данных на модуль
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_Generate_START( void );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция для конца отправки данных на модуль ( вызываеться по завершению )
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_Generate_STOP( void );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция отправки данных на модуль 1 байт
	* @param	( параметры ):	1 байт информации
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_WriteData( uint8_t oneByte );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция отправляет 1 байт в указаный сегмент
								( 8 пикселей = 8 битам ( 1 байт ) ) где 1 там вкл пиксель и наоборот
	* @param	( параметры ):	1 пар - номер сигмента, 2 пар - 1 байт для отображения
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_display_byte( uint8_t Seg_N, uint8_t DispData );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция включения и выключения экрана с сохранением на нем выведеной информации
	* @param	( параметры ):	байт статуса экрана = 1- вкл, 0- выкл
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_displayOnOff( uint8_t OnOff );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция отчистки дисплея
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_clearDisplay( void );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция установки яркости дисплея
	* @param	( параметры ):	яркость дисплея ( значения от 0  до 7 )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_brightness( uint8_t brightness );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция преобразования ASCII to UTF-8 для отображения кирилицы
	* @param	( параметры ):	массив ( строка ) с данными которую нужно преобразовать
	* @return  ( возвращает ):	указатель на память где храниться уже преобразованый массив

	******************************************************************************
*/
// функция для кодировки русских символов в UTF-8
extern char *pText;
// незабываем каждый раз после вызова функции utf8rus() освобождать память
// free( pText );	// освобождаем память выделенную в функции utf8rus() посредством malloc();
char *utf8rus( char *source );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция получения буффера для работы с ним
	* @param	( параметры ):	координата X и Y 
	* @return  ( возвращает ):	указатель на буффер

	******************************************************************************
*/
uint8_t* _getBufferPtr( int8_t x, int8_t y );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция заполнения буффера нужными пикселями
	* @param	( параметры ):	координаты X и Y и ( 0-выкл пиксель, 1-вкл пиксель )
	* @return  ( возвращает ):	

	******************************************************************************
*/
// меняя х у меняем положение текста вертикальное или горизонтальное
void setPixel( int8_t y, int8_t x, uint8_t enabled );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция из массива данных преобразует в пиксели и заполняет буффер
	* @param	( параметры ):	1 пар - ссылка на массив с данными, 2 пар и 3 пар - координаты X Y , 
								3 пар и 4 пар размер фрагмента ( например 8 на 8 пикселей )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void drawSprite( uint8_t* sprite, int x, int y, int width, int height );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция для преобразования полученного символа в его нарисованный вариант в массиве
	* @param	( параметры ):	1 пар - ссылка на текст, 2 пар - длина строки, 3 пар и 4 пар координаты X Y
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_drawString_buff(char* text, int len, int x, int y ); 
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция выводит на экран все что нвходиться в буффере
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void TM1640_display_Draw( void );
//----------------------------------------------------------------------------------

/*
	******************************************************************************
	* @brief	 ( описание ):  функция очистка буффера но не чистит экран
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void clear_buff( void );
//----------------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif

#endif	/*	_TM1640_H */

/************************ (C) COPYRIGHT GKP *****END OF FILE****/