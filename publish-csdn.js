const fs = require('fs');
const path = require('path');

const mdPath = process.argv[2];
if (!mdPath) {
  console.error('Usage: node publish-csdn.js <path-to-markdown-file>');
  process.exit(1);
}

const absoluteMdPath = path.resolve(mdPath);
const repoRoot = 'D:/STM32';
const relativeMdPath = path.relative(repoRoot, absoluteMdPath).replace(/\\/g, '/');
const notesDir = path.dirname(relativeMdPath);

console.log(`Processing: ${relativeMdPath}`);

let content = fs.readFileSync(absoluteMdPath, 'utf8');

const baseCdn = `https://cdn.jsdelivr.net/gh/Zyed816/STM32@main/${notesDir}/assets`;

// Replace with angle brackets: ](<./assets/filename>)  (handles spaces)
content = content.replace(/\]\(<\.\/assets\/([^>]+)>\)/g, (match, filename) => {
  const url = `${baseCdn}/${encodeURIComponent(filename)}`;
  console.log(`  (<>): ${filename}`);
  return `](${url})`;
});

// Replace without angle brackets: ](./assets/filename)
content = content.replace(/\]\(\.\/assets\/([^)]+)\)/g, (match, filename) => {
  const url = `${baseCdn}/${encodeURIComponent(filename)}`;
  console.log(`  : ${filename}`);
  return `](${url})`;
});

const ext = path.extname(absoluteMdPath);
const outPath = absoluteMdPath.replace(ext, `-csdn${ext}`);
fs.writeFileSync(outPath, content, 'utf8');
console.log(`\nCSDN-ready file written to: ${outPath}`);
