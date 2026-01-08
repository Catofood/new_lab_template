// Шаблон класса с документацией на русском
#pragma once
#include <string>
#include <vector>

/// Класс для обработки данных
class DataProcessor {
public:
  /// Конструктор с начальным значением
  explicit DataProcessor(int initial_value);
  
  /// Обрабатывает данные и возвращает результат
  std::vector<int> process(const std::vector<int>& input);
  
  /// Получает текущее значение
  int getValue() const noexcept;

private:
  int m_value;
  std::vector<int> m_cache;
};
