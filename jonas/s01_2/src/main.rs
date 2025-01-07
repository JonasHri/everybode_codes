use std::error::Error;
use std::fs;

fn main() -> Result<(), Box<dyn Error>> {
    let message: String = fs::read_to_string("input.txt")?;
    println!("{}", message);
    let mut sum: i32 = 0;
    let chars: Vec<char> = message.chars().collect();
    for i in (0..chars.len()).step_by(2) {
        let fir: char = chars[i];
        let sec: char = chars[i + 1];
        if chars[i] != 'x' && chars[i + 1] != 'x' {
            sum += 2;
        }
        sum += match fir {
            'B' => 1,
            'C' => 3,
            'D' => 5,
            _ => 0,
        };

        sum += match sec {
            'B' => 1,
            'C' => 3,
            'D' => 5,
            _ => 0,
        };
    }

    println!("{}", sum);
    Ok(())
}
