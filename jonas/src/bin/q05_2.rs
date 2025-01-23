use std::fs;

fn main() {
    let people_alt: Vec<Vec<usize>> =
        fs::read_to_string("./inputs/everybody_codes_e2024_q05_p2.txt")
            .unwrap()
            .lines()
            .map(|line| {
                line.split(' ')
                    .map(|x| str::parse::<usize>(x).unwrap())
                    .collect()
            })
            .collect();

    let mut people = vec![vec![0; people_alt.len()]; people_alt[0].len()];

    let mut seen_nums = vec![0; 100 * 100 * 100 * 100];

    for (i, col) in people_alt.iter().enumerate() {
        for (j, &val) in col.iter().enumerate() {
            people[j][i] = val;
        }
    }

    people.iter().for_each(|x| println!("{:?}", x));

    for i in 0..10e10 as usize {
        let cur_line = i % people.len();
        let next_line = (cur_line + 1) % people.len();
        let mover = people[cur_line].remove(0);
        let nl = people[next_line].len();
        let movepos = (mover - 1) % (2 * nl);
        if movepos < nl {
            people[next_line].insert(movepos, mover);
        } else {
            people[next_line].insert(2 * nl - movepos, mover);
        }
        let mut ran = 0;
        for j in 0..people.len() {
            ran *= 100;
            ran += people[j][0]
        }
        seen_nums[ran] += 1;
        if seen_nums[ran] == 2024 {
            println!("{} {} {}", ran * (i + 1), i + 1, ran);
            break;
        }
    }
}
