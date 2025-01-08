use std::fs;

fn main() {
    let data: Vec<String> = fs::read_to_string("everybody_codes_e2024_q07_p1.txt")
        .unwrap()
        .lines()
        .map(String::from)
        .collect();
    let steps = 10;
    let mut results: Vec<(&str, i32)> = vec![];
    for chariot in &data {
        let name_plan = chariot.split(":").collect::<Vec<&str>>();
        let name = name_plan[0];
        let plan = name_plan[1];
        let changes = plan.split(",").collect::<Vec<&str>>();
        let mut cur_power = 10;
        let mut collected_power = 0;
        for i in 0..steps {
            cur_power += match changes[i % changes.len()] {
                "+" => 1,
                "-" => -1,
                _ => 0,
            };
            collected_power += cur_power;
        }
        results.push((name, collected_power));
        println!("{}, {}", name, plan);
    }
    results.sort_by_key(|x| -x.1);

    for val in results {
        print!("{}", val.0);
    }
    println!();
}
