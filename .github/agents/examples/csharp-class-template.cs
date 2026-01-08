// Шаблон класса C# с валидацией
namespace Lab;

/// <summary>
/// Обработчик данных с валидацией
/// </summary>
public class DataProcessor
{
    private readonly int _value;

    /// <summary>
    /// Создаёт экземпляр обработчика
    /// </summary>
    /// <param name="value">Значение для обработки</param>
    /// <exception cref="ArgumentException">Если значение отрицательное</exception>
    public DataProcessor(int value)
    {
        if (value < 0)
            throw new ArgumentException(
                "Значение не может быть отрицательным", 
                nameof(value));
        
        _value = value;
    }

    /// <summary>
    /// Обрабатывает данные
    /// </summary>
    public void Process()
    {
        Console.WriteLine($"Обработка значения: {_value}");
    }

    /// <summary>
    /// Текущее значение
    /// </summary>
    public int Value => _value;
}
