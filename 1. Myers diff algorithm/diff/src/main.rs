#[derive(Debug)]
struct Line {
    number: usize,
    text: String,
}

fn lines(document: &[String]) -> Vec<Line> {
    document
        .iter()
        .enumerate()
        .map(|(i, text)| Line {
            number: i + 1,
            text: text.clone(),
        })
        .collect()
}

struct Myers<'a> {
    a: &'a [Line],
    b: &'a [Line],
}

impl<'a> Myers<'a> {
    fn new(a: &'a [Line], b: &'a [Line]) -> Self {
        Myers { a, b }
    }

    fn shortest_edit(&self) -> Option<usize> {
        let n = self.a.len();
        let m = self.b.len();
        let max = n + m;
        let mut v = vec![0; 2 * max + 1];
        let offset = max as isize;

        v[(offset + 1) as usize] = 0;

        for d in 0..=max {
            for k in (-((d as isize))..=(d as isize)).step_by(2) {
                let k_index = (offset + k) as usize;

                let mut x = if k == -((d as isize))
                    || (k != d as isize && v[(k_index - 1)] < v[(k_index + 1)])
                {
                    v[k_index + 1]
                } else {
                    v[k_index - 1] + 1
                };

                let mut y = (x as isize) - k;

                while x < n && (y as usize) < m && self.a[x].text == self.b[y as usize].text {
                    x += 1;
                    y += 1;
                }

                v[k_index] = x;

                if x >= n && (y as usize) >= m {
                    return Some(d);
                }
            }
        }

        None
    }
}

fn main() {
    let doc1 = vec![
        String::from("line one"),
        String::from("line two"),
        String::from("line three"),
    ];
    let doc2 = vec![
        String::from("line one"),
        String::from("line 2"),
        String::from("line three"),
    ];

    let a = lines(&doc1);
    let b = lines(&doc2);

    let myers = Myers::new(&a, &b);
    if let Some(d) = myers.shortest_edit() {
        println!("Shortest edit distance: {}", d);
    } else {
        println!("No edit path found");
    }
}
