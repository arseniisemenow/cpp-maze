
const markdownFilePath = 'README.md';

fetch(markdownFilePath)
    .then(response => response.text())
    .then(markdown => {
        const html = marked(markdown);

        document.getElementById('markdown-content').innerHTML = html;
    })
    .catch(error => console.error('Error fetching Markdown file:', error));