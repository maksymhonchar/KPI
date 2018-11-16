from flask import Flask
from flask import redirect, url_for, request, render_template
from werkzeug.exceptions import NotFound
from jsonreader import JsonReader

app = Flask(__name__)
posts_data = JsonReader()


@app.route('/')
def index():
    params = {
        'footer_needed': False,
    }
    return render_template('index.html', **params)


@app.route('/posts/')
def posts():
    params = {
        'footer_needed': True,
        'footer_address_needed': False,
        'posts_count': posts_data.getPostCount(),
        'posts': posts_data.getPostsList(),
    }
    return render_template('posts.html', **params)


@app.route('/posts/global_<int:fromID>_<int:postID>/')
def posts_postID(fromID, postID):
    params = {
        'footer_needed': False,
    }
    post = posts_data.getPost(postID)
    if not post or fromID != post[0]['from_id'] or postID != post[0]['post_id']:
        raise NotFound(description='Cannot find users {0} post with id {1}'.format(fromID, postID))
    params.update({'post': post[0]})
    return render_template('post_base.html', **params)


@app.route('/about/')
def about():
    params = {
        'footer_needed': False,
    }
    return render_template('about.html', **params)


@app.route('/contact/', methods=['POST', 'GET'])
def contact():
    params = {
        'footer_needed': True,
        'footer_address_needed': True,
    }
    if request.method == 'POST':
        return redirect(url_for('index'))
    return render_template('contact.html', **params)


@app.errorhandler(404)
def page_not_found(e):
    params = {
        'footer_needed': False,
        'error_msg': e,
    }
    return render_template('404.html', **params), 404


if __name__ == '__main__':
    app.run(debug=True, port=8000)
